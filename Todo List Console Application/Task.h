#pragma once
#include <iostream>
#include <string>
#include <vector>

struct Date
{
public:
	int mMonth = 0;
	int mDay = 0;
	int mYear = 0;
};

class Task
{
private:
	bool mIsDone; //is the task completed or not?
	std::string mTitle; //the title of the task
	std::string mDesc; //the description of the task
	Date mDate; //the due date of the task
	int mPriority; //the priority of the task

public:
	//default constructor, and constructor with params
	Task()
		: mIsDone(false), mTitle("DEFAULT TASK"), mDesc(""), mDate(Date()), mPriority(0) {}
	Task(std::string _title, std::string _desc = "", Date _date = Date(), int _priority = 0)
		: mIsDone(false), mTitle(_title), mDesc(_desc), mDate(_date), mPriority(_priority) {}

	//allows you to set a task to be equal to another task. //good for copying
	Task& operator=(Task& _task);

	//initialize or re-enter members of the task
	void setTitle(std::string _title) { mTitle = _title; }
	void setDesc(std::string _desc) { mDesc = _desc; }
	void setDate(Date _date) { mDate = _date; }
	void setPriority(int _priority) { mPriority = _priority; }

	//allows you to see what the members in the private section above have stored in them
	bool getIsDone() { return mIsDone; }
	std::string getTitle() { return mTitle; }
	std::string getDesc() { return mDesc; }
	Date getDate() { return mDate; }

	//easy ways to set the mIsDone member
	void Done() { mIsDone = true; }
	void Undo() { mIsDone = false; }

	//print out the task
	void PrintTask();
};