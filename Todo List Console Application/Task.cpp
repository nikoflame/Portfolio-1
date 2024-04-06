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

void Task::Serialize(std::ostream& _stream)
{
    //write mIsDone
    _stream.write((char*)&mIsDone, sizeof(bool));

    //write mTitle and mDesc
    size_t TitleSize = mTitle.size();
    size_t DescSize = mDesc.size();
    _stream.write((char*)&TitleSize, sizeof(size_t));
    _stream.write(mTitle.data(), TitleSize);
    _stream.write((char*)&DescSize, sizeof(size_t));
    _stream.write(mDesc.data(), DescSize);

    //write mDate
    _stream.write((char*)&mDate, sizeof(Date));

    //write mPriority
    _stream.write((char*)&mPriority, sizeof(int));
}

void Task::Deserialize(std::istream& _stream)
{
    //read mIsDone
    _stream.read((char*)&mIsDone, sizeof(bool));

    //read mTitle and mDesc
    size_t TitleSize, DescSize;
    _stream.read((char*)&TitleSize, sizeof(size_t));
    mTitle.resize(TitleSize);
    _stream.read((char*)&mTitle[0], TitleSize);
    _stream.read((char*)&DescSize, sizeof(size_t));
    mDesc.resize(DescSize);
    _stream.read((char*)&mDesc[0], DescSize);

    //read mDate
    _stream.read((char*)&mDate, sizeof(Date));

    //read mPriority
    _stream.read((char*)&mPriority, sizeof(int));
}
