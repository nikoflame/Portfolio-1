#pragma once
#include <string>
#include <vector>

class Task
{
private:
	bool mIsDone; //is the task completed or not?
	std::string mDesc; //the name/description of the task

public:
	//default constructor, and constructor with param for description
	Task()
		: mIsDone(false), mDesc("DEFAULT TASK") {}
	Task(std::string _desc)
		: mIsDone(false), mDesc(_desc) {}

	//allows you to set a task to be equal to another task. //good for copying
	Task& operator=(Task& _task);

	//initialize or re-enter the description of the task
	void setDesc(std::string _desc) { mDesc = _desc; }

	//allows you to see what the members in the private section above have stored in them
	bool getIsDone() { return mIsDone; }
	std::string getDesc() { return mDesc; }

	//easy ways to set the mIsDone member
	void Done() { mIsDone = true; }
	void Undo() { mIsDone = false; }
};

struct TaskList //a TaskList is simply a list (vector) of tasks.
{
public:
	std::vector<Task> mList;
};

