#include <iostream>
#include "Task.h"
#include "Utility.h"

int main()
{
    //initialize a todo list and a bool for if the file is opened
    std::vector<Task> TodoList;
    bool fopen = false;

    //read from file

    //print the todo list if there is one
    if (fopen) for (auto task : TodoList) task.PrintTask();
    
    //set up the main menu
    const char* MainMenuTitle = fopen ? "Would you like to edit your tasks?" : "Please select the first option to begin:";
    std::string MainMenu[] =
    {
        "Add a task",
        "Edit a task",
        "Delete a task",
        "Save and Exit"
    };
    int MainMenuChoice = Utility::MenuAndChoice(MainMenuTitle, MainMenu, 4);

    //Execute main menu
    bool MainMenuExit = false;
    do
    {
        switch (MainMenuChoice)
        {
        case 1: //add a task
        {
            break;
        }
        case 2: //edit a task
        {
            break;
        }
        case 3: //delete a task
        {
            break;
        }
        case 4: //save and exit
        default:
        {
            MainMenuExit = true;
            break;
        }
        }
    } while (!MainMenuExit);

    //exit gracefully
    return 0;
}