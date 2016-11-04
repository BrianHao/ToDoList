/*********************/
/** TODOLIST_DRIVER **/
/*********************/
/*
 ToDoListDriver provides an interface over two TaskLists—one that represents the outstanding
 tasks and another that represents the completed tasks. It provides functionality such as
 creating a new outstanding task, removing a specific outstanding task, marking a specific
 outstanding task as complete, and outputting the outstanding/completed tasks in
 non-detailed/detailed manners.
 */

#ifndef TODOLIST_DRIVER_CPP
#define TODOLIST_DRIVER_CPP

#include "ToDoListDriver.h"
#include "TaskList.h"
using namespace std;

// Moves a task from the Outstanding Tasks list to the Completed Tasks list
int ToDoListDriver::completeOutstandingTask(unsigned int pos) {
    Task* tempTask = outstandingTasks.taskPtrAt(pos);
    outstandingTasks.removeTask(pos);
    return completedTasks.addTask(tempTask);
}

#endif