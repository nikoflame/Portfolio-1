#include "Task.h"

Task& Task::operator=(Task& _task)
{
    mIsDone = _task.mIsDone;
    mDesc = _task.mDesc;
    return *this;
}
