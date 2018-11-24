#include "PersonalTank.h"


PersonalTank::PersonalTank(vector<vector<ViewableObject *> > &objects, int fieldWidthForBattle, int screenWidth, int dataArraySize) : objects(&objects), fieldWidthForBattle(fieldWidthForBattle), screenWidth(screenWidth), dataArraySize(dataArraySize)
{
	position = 0;

	needDrive = false;

	speed = 0;
	maxSpeed = 6;

	timerForSpeed = 0;

	highlightingUpdated = false;
	needUpdateTank = true;
	grupyAllocation.resize(10);
	controlIsPressed = false;
	numberIsPressed = 0;

	needAddBullet = false;
}

PersonalTank::~PersonalTank()
{

}


void PersonalTank::updateTracks()
{
	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			if ((*objects)[i][j] != nullptr && typeid(*(*objects)[i][j]) == typeid(Track))
			{
				(*objects)[i][j]->getComponentParameter()->backgroundIndex = ((*objects)[i][j]->getComponentParameter()->backgroundIndex + (speed > 0 ? (*objects)[i][j]->getComponentParameter()->numberOfVariant - 1 : 1)) % (*objects)[i][j]->getComponentParameter()->numberOfVariant;
				(*objects)[i][j]->needDraw = true;
			}
		}
	}
}


float PersonalTank::getAngelForGun(ViewableObject *gun, Vector2int mousePosition)
{
	if (gun->getComponentParameter()->name == "Determinators")
	{
		return 90.f;
	}

	float angel = getAngel(gun->getPosition() + Vector2int(gun->getComponentParameter()->xOffsetForBarrel, gun->getComponentParameter()->yOffsetForBarrel), mousePosition);
	if (gun->getComponentParameter()->horizontally)
	{
		if ((angel >= 0 && angel <= 60.f) || (angel >= 300.f && angel <= 360.f))
		{
			return 60.f;
		}
		else if ((angel >= 120.f && angel <= 180.f) || (angel >= 180.f && angel <= 240.f))
		{
			return 120.f;
		}
		else if (angel >= 60.f && angel <= 120.f)
		{
			return angel;
		}
		else
		{
			return angel - 180.f;
		}
	}
	else
	{
		if ((angel >= 30 && angel <= 90.f) || (angel >= 90.f && angel <= 150.f))
		{
			return 30.f;
		}
		else if ((angel >= 270.f && angel <= 330.f) || (angel >= 210.f && angel <= 270.f))
		{
			return 330.f;
		}
		else if ((angel >= 0.f && angel <= 30.f) || (angel >= 330.f && angel <= 360.f))
		{
			return angel;
		}
		else
		{
			return angel - 180.f;
		}
	}
}

void PersonalTank::updateGun(Vector2int mousePosition)
{
	for (int i = 0; i < int(highlightedItems.size()); ++i)
	{
		if ((*objects)[highlightedItems[i].x][highlightedItems[i].y]->getHealth() > 0 && typeid(*(*objects)[highlightedItems[i].x][highlightedItems[i].y]) == typeid(Gun))
		{
			(*objects)[highlightedItems[i].x][highlightedItems[i].y]->tiltAngle = getAngelForGun((*objects)[highlightedItems[i].x][highlightedItems[i].y], mousePosition);
		}
	}
}


float PersonalTank::getSpeedForVerticalGun(Vector2float first, Vector2float second, float angel)
{
	//v0 = ((x2-x1)/sin(a))*sqrt(g/(2*((y2-y1)+(x2-x1) / tg(a))))
	return ((second.x - first.x) / sin(angel * PI / 180.f)) * sqrt(GRAVITY / (2 * ((second.y - first.y) + (second.x - first.x) / tan(angel * PI / 180.f))));
}

void PersonalTank::makeShots(Vector2int mousePosition, vector<Component *> &components, int bulletPositionInComponents, long timer)
{
	for (int i = 0; i < int(highlightedItems.size()); ++i)
	{
		ViewableObject *gun = (*objects)[highlightedItems[i].x][highlightedItems[i].y];
		if (gun->getHealth() > 0 && timer - gun->timerForObject >= gun->getComponentParameter()->reload * 200)
		{
			gun->timerForObject = timer;
			int index = bulletPositionInComponents + gun->getComponentParameter()->indexOfComponents[0];

			ViewableObject *newBullet = new Bullet(components[index], index, gun, getAngelForGun(gun, mousePosition), float(gun->getComponentParameter()->bulletSpeed) / 2.f, gun->getPosition() + Vector2int(gun->getComponentParameter()->xOffsetForBarrel, gun->getComponentParameter()->yOffsetForBarrel) - globalOffset + getOffsetForTank(), timer);
			if (gun->getComponentParameter()->bulletSpeed == -1)
			{
				if ((newBullet->tiltAngle >= 0.f && newBullet->tiltAngle < 30.f) || (newBullet->tiltAngle > 330.f && newBullet->tiltAngle <= 360.f))
				{
					newBullet->speed = 100.f;
				}
				else
				{
					newBullet->speed = getSpeedForVerticalGun(newBullet->getBulletPosition(), mousePosition - globalOffset + getOffsetForTank(), newBullet->tiltAngle);
				}
			}
			newBullet->damage = gun->getComponentParameter()->damage;

			needAddBullet = true;
			bullets.push_back(newBullet);
		}
	}
}


void PersonalTank::removeHangingObjects()
{
	Vector2int mainPosition(-1, -1);

	for (int i = 0; i < int((*objects).size()) && mainPosition.x == -1; ++i)
	{
		for (int j = 0; j < int((*objects).size()) && mainPosition.x == -1; ++j)
		{
			if ((*objects)[i][j] != nullptr && typeid(*(*objects)[i][j]) == typeid(EngineRoom))
			{
				mainPosition = Vector2int(i, j);
			}
		}
	}

	vector<vector<pair<TankEditor::Direct, TankEditor::Direct> > > smallTank = TankEditor::getSmallTankForDfs(*objects);
	TankEditor::dfs(smallTank, mainPosition.x, mainPosition.y);

	for (int i = 0; i < int(smallTank.size()); ++i)
	{
		for (int j = 0; j < int(smallTank.size()); ++j)
		{
			if (smallTank[i][j].first != TankEditor::Direct::Nowhere)
			{
				(*objects)[i][j]->setHeath(0);
				needUpdateTank = true;
			}
		}
	}
}


Vector2int PersonalTank::getOffset()
{
	return Vector2int(xOffset, yOffset);
}

void PersonalTank::setOffset(Vector2int offset)
{
	setOffset(offset.x, offset.y);
}

void PersonalTank::setOffset(int x, int y)
{
	xOffset = x;
	position = 0;
	yOffset = y;
}


Vector2int PersonalTank::getGlobalOffset()
{
	return globalOffset;
}

Vector2int PersonalTank::getOffsetForTank()
{
	if (position == 0)
	{
		return Vector2int(xOffset, yOffset);
	}
	return Vector2int(xOffset + position, yOffset - globalOffset.y);
}


Vector2int PersonalTank::getBorder()
{
	vector<vector<bool> > smallTank = Tank::getSmallTank(*objects);

	Vector2int result(dataArraySize, -1);

	for (int i = 0; i < int(smallTank.size()); ++i)
	{
		for (int j = 0; j < int(smallTank.size()); ++j)
		{
			if (smallTank[i][j])
			{
				result.x = min(result.x, i);
				result.y = max(result.y, i);
			}
		}
	}
	return result;
}


void PersonalTank::setDrive(bool right)
{
	needDrive = true;
	driveRight = right;
}


int PersonalTank::getSpeed()
{
	return speed;
}

int PersonalTank::getMaxSpeed()
{
	return maxSpeed;
}


ViewableObject *PersonalTank::getViewableObject(Vector2int mousePosition)
{
	mousePosition = mousePosition - getOffsetForTank();

	int i = mousePosition.x / 20,
		j = mousePosition.y / 20;

	if (i < 0 || j < 0 || i >= dataArraySize || j >= dataArraySize)
	{
		return nullptr;
	}
	
	if ((*objects)[i][j] == nullptr)
	{
		return nullptr;
	}

	Vector2int objectPosition = (*objects)[i][j]->getPosition() / 20;
	return (*objects)[objectPosition.x][objectPosition.y];
}


void PersonalTank::setControlIsPressed(bool isPressed)
{
	controlIsPressed = isPressed;
}

void PersonalTank::setNumberIsPressed(int unicode)
{
	numberIsPressed = unicode - 26;
}


bool PersonalTank::getHighlightingUpdated(bool updated)
{
	if (highlightingUpdated)
	{
		if (!updated)
		{
			highlightingUpdated = false;
		}
		return true;
	}
	return false;
}

bool PersonalTank::getNeedUpdateTank()
{
	if (needUpdateTank)
	{
		needUpdateTank = false;
		return true;
	}
	return false;
}


bool PersonalTank::needHighlighte()
{
	return highlightedItems.size() != 0;
}

vector<ViewableObject *> PersonalTank::getHighlightedGuns(vector<Component *> &components, int allotmentPositionInComponents)
{
	vector<ViewableObject *> result;

	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			if ((*objects)[i][j] != nullptr)
			{
				(*objects)[i][j]->needDrawSeparately = false;
			}
		}
	}

	for (int i = 0; i < int(highlightedItems.size()); ++i)
	{
		if ((*objects)[highlightedItems[i].x][highlightedItems[i].y]->getHealth() > 0)
		{
			(*objects)[highlightedItems[i].x][highlightedItems[i].y]->needDrawSeparately = true;

			vector<Vector2int> offsetForHighlightedItems(4);
			offsetForHighlightedItems[1].x = (*objects)[highlightedItems[i].x][highlightedItems[i].y]->getComponentParameter()->width * 20;
			offsetForHighlightedItems[3].y = (*objects)[highlightedItems[i].x][highlightedItems[i].y]->getComponentParameter()->height * 20;
			offsetForHighlightedItems[2] = offsetForHighlightedItems[1] + offsetForHighlightedItems[3];

			int index;
			if ((*objects)[highlightedItems[i].x][highlightedItems[i].y]->getComponentParameter()->width == 1)
			{
				index = allotmentPositionInComponents + 1;
			}
			else
			{
				index = allotmentPositionInComponents + 3;
			}

			for (float phi = 0.f; phi < 360.f; phi += 90.f)
			{
				ViewableObject *newObject = new Allotment(components[index], index);
				newObject->tiltAngle = phi;
				newObject->setPosition(getOffsetForTank() + highlightedItems[i] * 20 + offsetForHighlightedItems[int(phi / 90.f)]);
				result.push_back(newObject);
			}
		}
	}

	int number = int(result.size());

	for (int i = 0; i < number; ++i)
	{
		ViewableObject *newObject = new Allotment(components[result[i]->getIndex() - 1], result[i]->getIndex() - 1);
		newObject->tiltAngle = result[i]->tiltAngle;
		newObject->setPosition(result[i]->getPosition());
		result.push_back(newObject);
	}
	return result;
}


bool PersonalTank::getNeedAddBullet()
{
	return needAddBullet;
}

vector<ViewableObject *> PersonalTank::getBullets()
{
	needAddBullet = false;

	vector<ViewableObject *> result = bullets;
	bullets.clear();

	return result;
}


void PersonalTank::work(Vector2int mousePosition, bool isPressed, long timer, int fps, vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets, bool rightIsPressed)
{
	//Work with motion
	if (needDrive)
	{
		needDrive = false;
		if (driveRight)
		{
			speed += maxSpeed / 6;
			speed = min(speed, maxSpeed);
		}
		else
		{
			speed -= maxSpeed / 6;
			speed = max(speed, -maxSpeed);
		}
	}

	if (speed != 0 && timer - timerForSpeed >= 100 - (100 * abs(speed)) / maxSpeed)
	{
		timerForSpeed = timer;
		updateTracks();

		globalOffset.x -= speed / abs(speed);
		Vector2int border = getBorder() * 20;
		border.y += 20;

		if (globalOffset.x <= 0 && globalOffset.x >= -(fieldWidthForBattle - screenWidth))
		{
			if (position < 0)
			{
				globalOffset.x = 0;
				position += 1;
			}
			else if (position > 0)
			{
				globalOffset.x = -(fieldWidthForBattle - screenWidth);
				position -= 1;
			}
			else
			{
				position = 0;
			}
		}
		else if (globalOffset.x > 0)
		{
			position -= 1;
			globalOffset.x = 0;
			if (position < -xOffset - border.x)
			{
				position = -xOffset - border.x;
			}
		}
		else if (globalOffset.x < -(fieldWidthForBattle - screenWidth))
		{
			position += 1;
			globalOffset.x = -(fieldWidthForBattle - screenWidth);
			if (position > screenWidth - xOffset - border.y)
			{
				position = screenWidth - xOffset - border.y;
			}
		}

		if (position != 0)
		{
			highlightingUpdated = true;
		}
	}

	//Work with highlighting
	if (numberIsPressed != -1 && controlIsPressed)
	{
		controlIsPressed = false;

		grupyAllocation[numberIsPressed] = highlightedItems;

		numberIsPressed = -1;
	}
	else if (numberIsPressed != -1)
	{
		highlightedItems = grupyAllocation[numberIsPressed];
		highlightingUpdated = true;

		numberIsPressed = -1;
	}
	else if (controlIsPressed)
	{
		controlIsPressed = false;
		ViewableObject *object = getViewableObject(mousePosition);

		if (object != nullptr && typeid(*object) == typeid(Gun) && object->getHealth() > 0)
		{
			bool repeatCheck = true;
			for (int i = 0; i < int(highlightedItems.size()) && repeatCheck; ++i)
			{
				if (object->getPosition() / 20 == highlightedItems[i])
				{
					repeatCheck = false;
				}
			}

			if (repeatCheck)
			{
				highlightedItems.push_back(object->getPosition() / 20);
				highlightingUpdated = true;
			}
		}
	}
	else if (isPressed)
	{
		ViewableObject *object = getViewableObject(mousePosition);

		if (object != nullptr && typeid(*object) == typeid(Gun) && object->getHealth() > 0)
		{
			highlightedItems.clear();
			highlightedItems.push_back(object->getPosition() / 20);
			highlightingUpdated = true;
		}
		else if (object == nullptr || object->getHealth() <= 0)
		{
			if (needHighlighte())
			{
				makeShots(mousePosition - getOffsetForTank(), components, bulletPositionInComponents, timer);
			}
		}
	}
	else if (rightIsPressed)
	{
		ViewableObject *object = getViewableObject(mousePosition);

		if (object != nullptr && typeid(*object) == typeid(Gun) && object->getHealth() > 0)
		{
			int objectPosition = -1;
			for (int i = 0; i < int(highlightedItems.size()); ++i)
			{
				if (object->getPosition() / 20 == highlightedItems[i])
				{
					objectPosition = i;
				}
			}

			if (objectPosition != -1)
			{
				highlightedItems.erase(highlightedItems.begin() + objectPosition);
				highlightingUpdated = true;
			}
		}
		else if ((object == nullptr || object->getHealth() <= 0) && highlightedItems.size() > 0)
		{
			highlightedItems.clear();
			highlightingUpdated = true;
		}
	}

	if (needHighlighte())
	{
		updateGun(mousePosition - getOffsetForTank());
	}
	
	//Work with bullet
	bool needRemoveHangingObjects = false;
	for (int k = 0; k < int(bullets.size()); ++k)
	{
		bool breakCheck = true;
		if (bullets[k]->getFather() != nullptr)
		{
			if (bullets[k]->getFather()->getHealth() > 0 && !collisionCheck(bullets[k]->getFather(), bullets[k], getBuletPositionFromTime(bullets[k], globalOffset - getOffsetForTank(), timer), globalOffset - getOffsetForTank()) && !bullets[k]->canDoDamageToItself)
			{
				bullets[k]->canDoDamageToItself = true;
			}
			else if (bullets[k]->getFather()->getHealth() > 0 && collisionCheck(bullets[k]->getFather(), bullets[k], getBuletPositionFromTime(bullets[k], globalOffset - getOffsetForTank(), timer), globalOffset - getOffsetForTank()) && bullets[k]->canDoDamageToItself)
			{
				bullets[k]->getFather()->setHeath(bullets[k]->getFather()->getHealth() - bullets[k]->damage);
				if (bullets[k]->getFather()->getHealth() <= 0)
				{
					highlightingUpdated = true;
					needRemoveHangingObjects = true;
				}
				bullets[k]->getFather()->needDraw = true;
				breakBullet(components, bulletPositionInComponents, bullets, k, timer);
				breakCheck = false;
			}
		}
		if (!breakCheck)
		{
			--k;
		}
	}
	
	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			if ((*objects)[i][j] != nullptr && (*objects)[i][j]->getHealth() > 0 && !(typeid(*(*objects)[i][j]) == typeid(AdditionToBigBlock) || typeid(*(*objects)[i][j]) == typeid(AdditionToEngineRoom) || typeid(*(*objects)[i][j]) == typeid(AdditionToGun) || typeid(*(*objects)[i][j]) == typeid(AdditionToTrack)))
			{
				for (int k = 0; k < int(bullets.size()); ++k)
				{
					if (bullets[k]->getFather() != (*objects)[i][j] && collisionCheck((*objects)[i][j], bullets[k], getBuletPositionFromTime(bullets[k], globalOffset - getOffsetForTank(), timer), globalOffset - getOffsetForTank()))
					{
						(*objects)[i][j]->setHeath((*objects)[i][j]->getHealth() - bullets[k]->damage);
						if ((*objects)[i][j]->getHealth() <= 0)
						{
							needUpdateTank = true;
							needRemoveHangingObjects = true;
							if (typeid(*(*objects)[i][j]) == typeid(Gun))
							{
								highlightingUpdated = true;
							}
						}
						(*objects)[i][j]->needDraw = true;
						
						breakBullet(components, bulletPositionInComponents, bullets, k, timer);
						--k;
					}
				}
			}
		}
	}

	if (needRemoveHangingObjects)
	{
		removeHangingObjects();
	}
}


void PersonalTank::download(string fileName, vector<Component *> &components)
{
	TankEditor tankEditor(*objects);

	tankEditor.download(fileName, components);
}