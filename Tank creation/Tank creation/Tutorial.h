#pragma once


#include "WorkWithWindow.h"


class Tutorial : public WorkWithWindow
{

public:
	Tutorial(string &fileName, Graphic *forCopyWindow);

	~Tutorial();

	void work();
};