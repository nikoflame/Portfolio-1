#include "App.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {
	//instantiate the main window
	pMainWindow = new MainWindow();

	//show the main window
	pMainWindow->Show();

	return true;
}