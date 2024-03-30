#pragma once
#include <iostream>
#include <string>

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
}