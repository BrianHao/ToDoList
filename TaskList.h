/*********************/
/** TASK_LIST CLASS **/
/*********************/
/*
 TaskList provides an interface over a data structure that stores many tasks. It provides 
 functionality such as getting a specific task from the list, adding a new task to the list, 
 removing a specific task from the list, and outputting all of the tasks in the list.
 
 The data structure used is a SortedVector, allowing for tasks to be sorted by deadline.
 */

#ifndef TASKLIST_H
#define TASKLIST_H

#include "SortedVector.h"
#include "Task.h"
#include <string>
#include <vector>
using namespace std;

class TaskList {
public:
    // Constructor and Destructor
    TaskList() {};
    virtual ~TaskList() {};
    
    // Functions to interact with the list of tasks
    void addTask(Task* inTask) { taskList.insert(inTask); };
    void addTaskFromSaveFormat(string saveFormat);
    string removeTask(unsigned int pos);
    Task getTask(unsigned int pos) { return *taskList.at(pos); };
    
    // Functions to output the list of tasks stored
    void printTaskList();
    void printTaskListDetailed();
    
    // Helper Functions
    vector<string> parseSaveFormat(const string &saveString, char delim);
    
private:    
    // Sorted Vector of task pointers
    SortedVector<Task*, Task::TaskPtrComparator> taskList;
};

#endif
