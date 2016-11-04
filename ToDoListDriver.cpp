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

#include <memory>
#include "ToDoListDriver.h"
#include "TaskList.h"
#include "Task.h"
using namespace std;

// Moves a task from the Outstanding Tasks list to the Completed Tasks list
unsigned int ToDoListDriver::completeOutstandingTask(unsigned int pos) {
    // If position is out of bounds, return
    if (pos > outstandingTasks.size()) {
        return -1;
    }
    // Creates a temporary task pointer and sets it to the task at the provided position
    shared_ptr<Task> tempTask = outstandingTasks.taskPtrAt(pos);
    // Removes the position at provided position
    outstandingTasks.removeTask(pos);
    // Adds the task to the completed task list, returns the position it was inserted into
    return completedTasks.addTask(tempTask);
}

#endif
