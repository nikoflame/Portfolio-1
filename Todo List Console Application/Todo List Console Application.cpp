#include <iostream>
#include "Task.h"
#include "Utility.h"

int main()
{
    //initialize a list of TaskLists and a bool for if the file is opened
    std::vector<TaskList> ListOfLists;
    bool fopen = false;

    //read from file
     
    //set up the main menu
    const char* MainMenuTitle = "Please choose an option:";
    std::string MainMenu[] =
    {
        "Create Todo List",
        "Delete Todo List",
        "View/Edit Todo List"
    };
    int MainMenuChoice = Utility::MenuAndChoice(MainMenuTitle, MainMenu, fopen ? 3 : 1); //if file didn't open, only show first menu option.

    //exit gracefully
    return 0;
}