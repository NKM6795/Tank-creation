#include "BotTank.h"



BotTank::BotTank(vector<vector<ViewableObject *> > &objects, int fieldWidthForBattle, int screenWidth, int dataArraySize) : PersonalTank(objects, fieldWidthForBattle, screenWidth, dataArraySize)
{
	needAnalysis = true;
}


BotTank::~BotTank()
{

}


Vector2int BotTank::getPositionInBot(Vector2int positionForConvert)
{
	return Vector2int((getOffsetForTank() * 2 - positionForConvert).x + dataArraySize * 20, positionForConvert.y) - getOffsetForTank();
}


void BotTank::analysis(Tank &personalTank, Vector2int personalPosition)
{
	if ((getOffsetForTank() - personalPosition).x > dataArraySize * 20 + 80)
	{
		speed = -maxSpeed;
	}
	else
	{
		speed = 0;
	}

	oldPositionOfPersonalTank = personalPosition;

	needAnalysis = false;

	grupyAllocation.clear();

	grupyAllocation.resize(2);

	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			if (checkForExistenceAndNotComplementarity((*objects)[i][j]) && typeid(*(*objects)[i][j]) == typeid(Gun))
			{
				if ((*objects)[i][j]->getComponentParameter()->horizontally)
				{
					grupyAllocation[0].push_back((*objects)[i][j]->getPosition() / 20);
				}
				else
				{
					grupyAllocation[1].push_back((*objects)[i][j]->getPosition() / 20);
				}
				(*objects)[i][j]->needDrawSeparately = true;
			}
		}
	}

	Vector2int mainPosition(-1, -1);

	vector<vector<ViewableObject *> > personalTankObjects = personalTank.getViewableObjects();

	for (int i = 0; i < int(personalTankObjects.size()); ++i)
	{
		for (int j = 0; j < int(personalTankObjects.size()); ++j)
		{
			if (personalTankObjects[i][j] != nullptr && personalTankObjects[i][j]->getHealth() > 0 && typeid(*personalTankObjects[i][j]) == typeid(EngineRoom))
			{
				mainPosition = Vector2int(i, j);
			}
		}
	}

	prisesPosition.clear();
	if (mainPosition.x != -1)
	{
		prisesPosition.push_back(mainPosition * 20 + Vector2int(30, 20) + personalPosition);
		prises.push_back(personalTankObjects[mainPosition.x][mainPosition.y]);
	}
}


void BotTank::makeShots(Vector2int mousePosition, vector<Component *> &components, int bulletPositionInComponents, long timer)
{
	for (int i = 0; i < int(highlightedItems.size()); ++i)
	{
		ViewableObject *gun = (*objects)[highlightedItems[i].x][highlightedItems[i].y];
		if (gun->getHealth() > 0 && timer - gun->timerForObject >= gun->getComponentParameter()->reload * 200)
		{
			gun->timerForObject = timer;
			int index = bulletPositionInComponents + gun->getComponentParameter()->indexOfComponents[0];

			Vector2int bulletPositionInTank = gun->getPosition() + Vector2int(gun->getComponentParameter()->xOffsetForBarrel, gun->getComponentParameter()->yOffsetForBarrel),
				bulletPosition = Vector2int(dataArraySize * 20 - bulletPositionInTank.x, bulletPositionInTank.y) + getOffsetForTank();

			ViewableObject *newBullet = new Bullet(components[index], index, gun, getAngelForGun(gun, mousePosition), float(gun->getComponentParameter()->bulletSpeed) / 2.f, bulletPosition, timer);
			if (gun->getComponentParameter()->bulletSpeed == -1)
			{
				if ((newBullet->tiltAngle >= 0.f && newBullet->tiltAngle < 30.f) || (newBullet->tiltAngle > 330.f && newBullet->tiltAngle <= 360.f))
				{
					newBullet->speed = 100.f;
				}
				else
				{
					newBullet->speed = getSpeedForVerticalGun(bulletPositionInTank, mousePosition, newBullet->tiltAngle);
				}
			}
			newBullet->tiltAngle = 360.f - newBullet->tiltAngle;
			newBullet->damage = gun->getComponentParameter()->damage;

			needAddBullet = true;
			bullets.push_back(newBullet);
		}
	}
}


void BotTank::updateTracks()
{
	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			if ((*objects)[i][j] != nullptr && typeid(*(*objects)[i][j]) == typeid(Track))
			{
				(*objects)[i][j]->timerForObject = ((*objects)[i][j]->timerForObject + (speed > 0 ? (*objects)[i][j]->getComponentParameter()->numberOfVariant - 1 : 1)) % (*objects)[i][j]->getComponentParameter()->numberOfVariant;
				(*objects)[i][j]->needDraw = true;
			}
		}
	}
}


void BotTank::setGlobalOffset(Vector2int offset)
{
	globalOffset = offset;
}

Vector2int BotTank::getOffsetForTank()
{
	if (position == 0)
	{
		return Vector2int(xOffset, yOffset) - globalOffset;
	}
	return Vector2int(xOffset + position, yOffset - globalOffset.y) - globalOffset;
}


Vector2int BotTank::getBorder()
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

	++result.y;
	result = Vector2int(dataArraySize - result.y, dataArraySize - result.x) * 20;

	return result;
}


void BotTank::work(long timer, int fps, int lengthBetweenTanks, Vector2int personalPosition, vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets, Tank &personalTank)
{
	if (needAnalysis && false)
	{
		analysis(personalTank, personalPosition);
	}

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
		Vector2int border = getBorder();

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
			//else if (getOffsetForTank().x + border.x < personalPosition.x + lengthBetweenTanks)
			//{
			//	globalOffset.x -= 1;
			//}
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


	if (prisesPosition.size() > 0)
	{
		Vector2int positionOfPrice = getPositionInBot(prisesPosition[0]);

		//Horisontal guns
		{
			highlightedItems = grupyAllocation[0];

			updateGun(positionOfPrice);
			makeShots(positionOfPrice, components, bulletPositionInComponents, timer);
		}

		//Vertical guns
		{
			highlightedItems = grupyAllocation[1];

			updateGun(positionOfPrice);
			makeShots(positionOfPrice, components, bulletPositionInComponents, timer);
		}
	}

	//Work with bullet
	bool needRemoveHangingObjects = false;
	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			if (checkForExistenceAndNotComplementarity((*objects)[i][j]))
			{
				for (int k = 0; k < int(bullets.size()); ++k)
				{
					Vector2int bulletPosition = getBuletPositionFromTime(bullets[k], timer),
						offsetForBullet = Vector2int((Vector2int(dataArraySize * 20, 0) - (bulletPosition - getOffsetForTank()) - bulletPosition).x, -getOffsetForTank().y);
					if (bullets[k]->getFather() != (*objects)[i][j])
					{
						if (collisionCheck((*objects)[i][j], bullets[k], bulletPosition, offsetForBullet))
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

							breakBullet(components, bulletPositionInComponents, bullets, k, timer - fps, !(*objects)[i][j]->getComponentParameter()->canRebound || bullets[k]->getFather()->getComponentParameter()->name == "Thor's Hummer", objects, Vector2int(i, j), offsetForBullet);
							--k;
						}
					}
					else
					{
						if (bullets[k]->getFather()->getHealth() > 0 && !collisionCheck(bullets[k]->getFather(), bullets[k], bulletPosition, offsetForBullet) && !bullets[k]->canDoDamageToItself)
						{
							bullets[k]->canDoDamageToItself = true;
						}
						else if (bullets[k]->getFather()->getHealth() > 0 && collisionCheck(bullets[k]->getFather(), bullets[k], bulletPosition, offsetForBullet) && bullets[k]->canDoDamageToItself)
						{
							bullets[k]->getFather()->setHeath(bullets[k]->getFather()->getHealth() - bullets[k]->damage);
							if (bullets[k]->getFather()->getHealth() <= 0)
							{
								highlightingUpdated = true;
								needRemoveHangingObjects = true;
							}
							bullets[k]->getFather()->needDraw = true;
							breakBullet(components, bulletPositionInComponents, bullets, k, timer);
							--k;
						}
					}
				}
			}
		}
	}

	if (needRemoveHangingObjects)
	{
		removeHangingObjects();
		needUpdateLengthBetweenTanks = true;
	}

	if (timer - timerForAnalysis > 10000 || (prises.size() && prises.back()->getHealth() <= 0) || abs(oldPositionOfPersonalTank.x - personalPosition.x) > 20 || speed != 0)
	{
		timer = timerForAnalysis;
		needAnalysis = true;
	}
}