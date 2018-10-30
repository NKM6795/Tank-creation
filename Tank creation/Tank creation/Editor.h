#pragma once


#include "WorkWithWindow.h"


class Editor : public WorkWithWindow
{


public:
	Editor(string &fileName);

	Editor(string &fileName, Graphic *forCopyWindow);


	void work();
};