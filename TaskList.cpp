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

const char DELIM = '|';

// Creates a new Task using the save format, and then adds that task to the list.
// Additionally, returns the position the task was inserted into.
unsigned int TaskList::addTask(const string& saveString) {
    // Convert passed string in the save format into a vector
    vector<string> saveVector = parseSaveFormat(saveString, DELIM);
    
    // Create a new task based on the vector contents
    Task* newTask;
    string taskType = saveVector[0];
    unsigned int newDeadline = stoi(saveVector[1]);
    string newDescription = saveVector[2];
    
    // If Task Type is an Event Task, create a new event task and set it to newTask
    if (taskType == "E") {
        EventTask* e = new EventTask(newDeadline, newDescription);
        e->setLocation(saveVector[3]);
        e->setTime(saveVector[4]);
        newTask = e;
    }
    // If Task Type is a Shopping Task, create a new event task and set it to newTask
    else if (taskType == "S") {
        ShoppingTask* s = new ShoppingTask(newDeadline, newDescription);
        if (saveVector.size() > 3) {
            for (int i = 3; i < saveVector.size(); i++) {
                s->addItem(saveVector[i]);
            }
        }
        newTask = s;
    }
    // If Task Type is a Homework Task, create a new event task and set it to newTask
    else if (taskType == "H") {
        HomeworkTask* h = new HomeworkTask(newDeadline, newDescription);
        h->setSubject(saveVector[3]);
        newTask = h;
    }
    // If Task Type is none of the above, it is a General Task
    else {
        newTask = new Task(newDeadline, newDescription);
    }
    
    // Add the new task to the list
    return addTask(newTask);
}

// Removes a task at the provided position, returning it in its save format
string TaskList::removeTask(unsigned int pos)  {
    string removedTaskSaveFormat = taskList.at(pos)->toSaveFormat();
    taskList.remove(pos);
    return removedTaskSaveFormat;
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
// Takes in a string in the Save Format and parses the contents into a vector of strings
vector<string> TaskList::parseSaveFormat(const string saveString, char delim) {
    stringstream ss(saveString);
    string item;
    vector<string> saveVector;
    while (getline(ss, item, delim)) {
        saveVector.push_back(item);
    }
    return saveVector;
}

#endif
