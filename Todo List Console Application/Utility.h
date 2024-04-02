#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include "Task.h"

namespace Utility
{
	//clears the std::cin buffer
	inline void clrcin()
	{
		std::cin.clear();
		std::cin.ignore();
	}

	//sends a message to the user and asks for input, then validates that input to be legal and within range if needed
	inline int GetValidatedInt(const char* strMessage, int nMinimumRange = 0, int nMaximumRange = 0)
	{
		int userInput;

		//loop until break
		do
		{
			//message
			std::cout << strMessage;

			//retrieve input
			std::cin >> userInput;

			//int validation failed
			while (std::cin.fail())
			{
				clrcin();
				std::cout << "\nInvalid input. Please try again: ";
				std::cin >> userInput;
			}

			//check range
			if ((nMinimumRange != 0 || nMaximumRange != 0) && (userInput < nMinimumRange || userInput > nMaximumRange))
			{
				//range check bad
				std::cout << "You entered a number out of the allowed range. ";
				if (nMinimumRange != 0)
					std::cout << "The minimum range is " << nMinimumRange << ". ";
				if (nMaximumRange != 0)
					std::cout << "The maximum range is " << nMaximumRange << ". ";
				std::cout << "Please try again." << std::endl;
				clrcin();
			}
			else
			{
				//range check good
				clrcin();
				break;
			}
		} while (true);

		return userInput;
	}

	//outputs an array of strings into a numbered menu, with a title, then asks the user to choose one and validates their response
	inline int MenuAndChoice(const char* menuTitle, const std::string menu[], int menuSize)
	{
		//print menu
		std::cout << menuTitle << std::endl;
		for (int i = 0; i < menuSize; i++) {
			std::cout << i + 1 << ". " << menu[i] << std::endl;
		}

		// Get user's selection
		int choice = GetValidatedInt("Choose One: ", 1, menuSize);

		return choice;
	}

	//strips a string of its empty space characters at the beginning and end
	inline std::string StripString(std::string& s)
	{
		// Remove trailing whitespace
		while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\n')) {
			s.pop_back();
		}

		// Remove leading whitespace
		size_t start = 0;
		while (start < s.size() && (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')) {
			++start;
		}
		s = s.substr(start);

		return s;
	}

	//checks if a string is in a valid MM/DD/YYYY date format and returns an error code (0 = good, 1 = format, 2 = range)
	inline int isValidDate(const std::string& dateString)
	{
		//regular expression for MM/DD/YYYY format
		std::regex dateRegex("^\\d{2}/\\d{2}/\\d{4}$");

		//if it's in the wrong format, return 0
		if (!std::regex_match(dateString, dateRegex)) return 1; //ERROR CODE 1 = WRONG FORMAT

		//extract month, day, and year from the string using stringstream
		std::stringstream ss(dateString);
		char delimiter;
		int month, day, year;
		ss >> month >> delimiter >> day >> delimiter >> year;

		// Check if month, day, and year are within valid ranges
		if (month < 1 || month > 12 || day < 1 || day > 31 || year < 1000 || year > 9999) return 2; //ERROR CODE 2 = INVALID RANGE

		return 0; //ERROR CODE 0 = GOOD
	}

	inline Task AddTask()
	{
		//create a task
		Task task;

		//set the title
		std::cout << "Please enter a name for your task and press enter. Alternatively, you may press enter with no input to go back to the main menu.\nName of task >> ";
		std::string title = "";
		std::getline(std::cin, title);
		StripString(title);
		if (title == "") return task;
		task.setTitle(title);

		//set the description
		std::cout << "Please enter a description for your task and press enter. Alternatively, you may press enter with no input to skip this.\nDescription of task >> ";
		std::string desc = "";
		std::getline(std::cin, desc);
		StripString(desc);
		if (desc != "") task.setDesc(desc);

		//set the due date
		while (true)
		{
			std::cout << "Please enter a due date for your task and press enter. Alternatively, you may press enter with no input to skip this.\nDue date of task (MM/DD/YYYY) >> ";
			std::string date = "";
			std::getline(std::cin, date);
			StripString(date);
			if (date == "") break;
			if (isValidDate(date) == 0)
			{
				Date d;
				std::stringstream ss(date);
				char delimiter;
				ss >> d.mMonth >> delimiter >> d.mDay >> delimiter >> d.mYear;
				task.setDate(d);
				break;
			}
			if (isValidDate(date) == 1) std::cout << "Invalid date format. Please enter a date in MM/DD/YYYY format.\n";
			else std::cout << "Invalid integer range. Please enter a valid month, day, and year.\n";
		}

		//set the priority
		task.setPriority(GetValidatedInt("Please enter a priority for your task and press enter. Default priority is 0.\nPriority >> "));

		//return the completed task
		return task;
	}

	inline void EditTask(Task& t)
	{
		//set up the edit menu
		const char* EditMenuTitle = "Please choose an option:";
		std::string EditMenu[] =
		{
			"Mark as complete/undo",
			"Change name/title",
			"Change description",
			"Remove description",
			"Change due date",
			"Remove due date",
			"Change priority",
			"Back to main menu"
		};
		bool EditMenuExit = false;

		//set up yes or no menu
		std::string menuYN[] = { "Yes", "No" };

		//execute edit menu
		do
		{
			//print edit menu and collect user input
			int EditMenuChoice = MenuAndChoice(EditMenuTitle, EditMenu, 8);
			switch (EditMenuChoice)
			{
			case 1: //mark as complete/undo
			{
				if (t.getIsDone()) t.Undo();
				else t.Done();
				break;
			}
			case 2: //change name/title
			{
				std::cout << "Please enter a new name for the task (enter nothing for no change): ";
				std::string title = "";
				std::getline(std::cin, title);
				StripString(title);
				if (title != "") t.setTitle(title);
				break;
			}
			case 3: //change description
			{
				std::cout << "Please enter a new description for the task (enter nothing for no change): ";
				std::string desc = "";
				std::getline(std::cin, desc);
				StripString(desc);
				if (desc != "") t.setDesc(desc);
				break;
			}
			case 4: //delete description
			{
				int menuYNChoice = Utility::MenuAndChoice("Are you sure you would like to delete your description? ", menuYN, 2);
				if (menuYNChoice == 1) t.setDesc("");
				break;
			}
			case 5: //change due date
			{
				while (true)
				{
					std::cout << "Please enter a new due date for your task and press enter (enter nothing for no change):\nDue date of task (MM/DD/YYYY) >> ";
					std::string date = "";
					std::getline(std::cin, date);
					StripString(date);
					if (date == "") break;
					if (isValidDate(date) == 0)
					{
						Date d;
						std::stringstream ss(date);
						char delimiter;
						ss >> d.mMonth >> delimiter >> d.mDay >> delimiter >> d.mYear;
						t.setDate(d);
						break;
					}
					if (isValidDate(date) == 1) std::cout << "Invalid date format. Please enter a date in MM/DD/YYYY format.\n";
					else std::cout << "Invalid integer range. Please enter a valid month, day, and year.\n";
				}
				break;
			}
			case 6: //delete due date
			{
				int menuYNChoice = Utility::MenuAndChoice("Are you sure you would like to delete your due date? ", menuYN, 2);
				if (menuYNChoice == 1) t.setDate(Date());
				break;
			}
			case 7: //change priority
			{
				int p = Utility::GetValidatedInt("Please enter a new priority for the task: ");
				t.setPriority(p);
				break;
			}
			case 8: //back to main menu
			default:
			{
				EditMenuExit = true;
				break;
			}
			}
		} while (!EditMenuExit);
	}
}