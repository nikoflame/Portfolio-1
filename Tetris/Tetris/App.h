#pragma once

#include "wx/wx.h"
#include "MainWindow.h"

class App : public wxApp
{
private:
	MainWindow* pMainWindow = nullptr; //the main window
public:
	App();
	~App();
	virtual bool OnInit();
};