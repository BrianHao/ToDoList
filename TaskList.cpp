/***************/
/** TASK_LIST **/
/***************/
/*
 TaskList provides an interface over a data structure that stores many tasks. It provides
 functionality such as getting a specific task from the list, adding a new task to the list,
 removing a specific task from the list, and outputting all of the tasks in the list.
 
 The data structure used is a SortedVector, allowing for tasks to be sorted by deadline.
 */

#ifndef TASKLIST_CPP
#define TASKLIST_CPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "TaskList.h"
#include "Task.h"
using namespace std;

// Outputs a list of all stored tasks
void TaskList::printTaskList() {
    if (taskList.size() > 0) {
        for (int i = 0; i < taskList.size(); i++) {
            cout << i+1 << ". ";
            taskList.at(i)->print();
        }
    }
}

// Outputs a detailed list of all stored tasks
void TaskList::printTaskListDetailed() {
    if (taskList.size() > 0) {
        for (int i = 0; i < taskList.size(); i++) {
            cout << i+1 << ". ";
            taskList.at(i)->printDetailed();
        }
    }
}

#endif
