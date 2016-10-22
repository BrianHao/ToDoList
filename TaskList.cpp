/*********************/
/** TASK_LIST CLASS **/
/*********************/
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

// Creates a new Task using the save format, and then adds that task to the list.
void TaskList::addTaskFromSaveFormat(string saveFormat) {
    vector<string> saveVector = parseSaveFormat(saveFormat);
    
    
}


string TaskList::removeTask(unsigned int pos)  {
    return "";
}

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

// Helper Function
// Parses a string in the save format and transfers contents into a vector of strings
vector<string> parseSaveFormat(const string &saveString, char delim) {
    stringstream ss(saveString);
    string item;
    vector<string> saveVector;
    while (getline(ss, item, delim)) {
        saveVector.push_back(item);
    }
    return saveVector;
}

#endif
