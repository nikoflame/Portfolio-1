#include <iostream>
#include <algorithm>
#include <fstream>
#include "Task.h"
#include "Utility.h"

int main()
{
    //initialize a todo list and a bool for if the file is opened
    std::vector<Task> TodoList;

    //open file
    std::fstream fin;
    fin.open("list.bin", std::ios_base::in | std::ios_base::binary);

    //read from file
    if (fin.is_open())
    {
        //read size
        size_t numTasks;
        fin.read((char*)&numTasks, sizeof(size_t));

        //read file
        for (int i = 0; i < numTasks; i++)
        {
            Task task;
            task.Deserialize(fin);
            TodoList.push_back(task);
        }

        //close file
        fin.close();
    }
    
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
        system("cls");

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
            std::cout << "Your Todo List:\n";
            for (Task task : TodoList) task.PrintTask();
            std::cout << std::endl;
        }

        //print main menu and collect user input
        int MainMenuChoice = Utility::MenuAndChoice(MainMenuTitle, MainMenu, 4);
        system("cls");
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
            if (TodoList.size() == 0)
            {
                std::cout << "Please add a task to your todo list first!\n";
                system("pause");
            }
            else
            {
                std::cout << "Please choose a task to edit:\n\n";
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
            if (TodoList.size() == 0)
            {
                std::cout << "Please add a task to your todo list first!\n";
                system("pause");
            }
            else
            {
                std::cout << "Please choose a task to delete:\n";
                for (int i = 0; i < TodoList.size(); i++)
                {
                    std::cout << i + 1 << ". ";
                    TodoList[i].PrintTask();
                }
                int TaskToDelete = Utility::GetValidatedInt("\nChoose one: ", 1, TodoList.size());

                system("cls");
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

    //file output
    if (TodoList.size() > 0)
    {
        //open file
        std::fstream fout;
        fout.open("list.bin", std::ios_base::out | std::ios_base::binary);

        //write to file
        size_t numTasks = TodoList.size();
        fout.write((char*)&numTasks, sizeof(size_t));
        for (Task task : TodoList)
            task.Serialize(fout);

        //close file
        fout.close();
    }
    else remove("list.bin");

    //exit gracefully
    return 0;
}