#pragma once


#include "NotificationWindow.h"


class BattleResult : public NotificationWindow
{

public:
	BattleResult(string &fileName, Graphic *forCopyWindow, string massage1 = "You win!", string massage2 = "Max cost was increased on 200", string massage3 = "New max cost");


	void work();
};