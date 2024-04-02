#include <iostream>
#include <algorithm>
#include "Task.h"
#include "Utility.h"

int main()
{
    //initialize a todo list and a bool for if the file is opened
    std::vector<Task> TodoList;
    bool fopen = false;

    //read from file
    
    //set up the main menu
    const char* MainMenuTitle = TodoList.size() > 0 ? "What would you like to do?" : "Please select the first option to begin:";
    std::string MainMenu[] =
    {
        "Add a task",
        "Edit a task",
        "Delete a task",
        "Save and Exit"
    };
    bool MainMenuExit = false;

    //Execute main menu
    do
    {
        //organize and print the todo list if there is one
        if (TodoList.size() != 0)
        {
            if (TodoList.size() > 1)
            {
                for (int i = 0; i < TodoList.size() - 1; i++)
                    for (int j = 0; j < TodoList.size() - i - 1; j++)
                        if (TodoList[j].getPriority() < TodoList[j + 1].getPriority())
                        {
                            Task temp = TodoList[j];
                            TodoList[j] = TodoList[j + 1];
                            TodoList[j + 1] = temp;
                        }
            }
            for (Task task : TodoList) task.PrintTask();
        }

        //print main menu and collect user input
        int MainMenuChoice = Utility::MenuAndChoice(MainMenuTitle, MainMenu, 4);
        switch (MainMenuChoice)
        {
        case 1: //add a task
        {
            Task task = Utility::AddTask();
            if (task.getTitle() != "DEFAULT TASK") TodoList.push_back(task);
            break;
        }
        case 2: //edit a task
        {
            if (TodoList.size() == 0) std::cout << "Please add a task to your todo list first!\n";
            else
            {
                std::cout << "Please choose a task to edit:\n";
                for (int i = 0; i < TodoList.size(); i++)
                {
                    std::cout << i + 1 << ". ";
                    TodoList[i].PrintTask();
                }
                int TaskToEdit = Utility::GetValidatedInt("\nChoose one: ", 1, TodoList.size());
                Utility::EditTask(TodoList[TaskToEdit - 1]);
            }
            break;
        }
        case 3: //delete a task
        {
            if (TodoList.size() == 0) std::cout << "Please add a task to your todo list first!\n";
            else
            {
                std::cout << "Please choose a task to delete:\n";
                for (int i = 0; i < TodoList.size(); i++)
                {
                    std::cout << i + 1 << ". ";
                    TodoList[i].PrintTask();
                }
                int TaskToDelete = Utility::GetValidatedInt("\nChoose one: ", 1, TodoList.size());

                std::cout << "This is the task you chose to delete:\n";
                TodoList[TaskToDelete - 1].PrintTask();
                
                std::string menuYN[] = {"Yes", "No"};
                int menuYNChoice = Utility::MenuAndChoice("\nAre you sure you want to delete this task? ", menuYN, 2);

                if (menuYNChoice == 1) TodoList.erase(TodoList.begin() + (TaskToDelete - 1));
            }
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