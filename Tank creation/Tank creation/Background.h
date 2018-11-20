#pragma once


#include "ViewableObject.h"


class BackgroundComponent : public Component
{

public:
	BackgroundComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant);


};


class Background : public ViewableObject
{


public:
	Background();
	Background(Component *component);
	Background(Component *component, int index);


};


class BackgroundForBattleComponent : public Component
{

public:
	BackgroundForBattleComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, vector<Vector2int> dimensions, vector<Vector2int> offsets);


};


class BackgroundForBattle : public ViewableObject
{


public:
	BackgroundForBattle();
	BackgroundForBattle(Component *component);
	BackgroundForBattle(Component *component, int index);


};

