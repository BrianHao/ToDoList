/***************/
/** TASK_LIST **/
/***************/
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
    unsigned int addTask(Task* inTask) { return taskList.insert(inTask); };
    unsigned int addTask(const string &saveString);
    string removeTask(unsigned int pos);
    Task taskAt(unsigned int pos) { return *taskList.at(pos); };
    Task* taskPtrAt(unsigned int pos) { return taskList.at(pos); };
    
    // Functions to output the list of tasks stored
    void printTaskList();
    void printTaskListDetailed();
    
    // Helper Functions
    bool empty() { return taskList.size() == 0; };
    // Takes in a string in the Save Format and parses the contents into a vector of strings
    vector<string> parseSaveFormat(const string saveString, char delim);
    
private:    
    // Sorted Vector of task pointers
    SortedVector<Task*, Task::TaskPtrComparator> taskList;
};

#endif
