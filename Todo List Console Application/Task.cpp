#include "Task.h"

Task& Task::operator=(const Task& _task)
{
    mIsDone = _task.mIsDone;
    mTitle = _task.mTitle;
    mDesc = _task.mDesc;
    mDate = _task.mDate;
    mPriority = _task.mPriority;
    return *this;
}

void Task::PrintTask()
{
    //print [ ] if the task is not done, or [X] if it is done
    std::cout << "[";
    if (mIsDone) std::cout << "X";
    else std::cout << " ";
    std::cout << "] ";

    //print the title
    std::cout << mTitle << "\t";

    //print the date if there is one
    if (mDate.mDay != 0)
    {
        std::cout << "Due: ";
        if (mDate.mMonth < 10) std::cout << "0";
        std::cout << mDate.mMonth << "/";
        if (mDate.mDay < 10) std::cout << "0";
        std::cout << mDate.mDay << "/" << mDate.mYear << "\t";
    }

    //print the priority
    std::cout << "Priority: " << mPriority;

    //print the description if there is one
    if (mDesc != "") std::cout << "\n\t" << mDesc;
    
    //end the line
    std::cout << std::endl;
}
