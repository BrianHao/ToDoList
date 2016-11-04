/***************/
/** TASK_LIST **/
/***************/
/*
 TaskList provides an interface over a data structure that stores many tasks. It provides 
 functionality such as getting a specific task from the list, adding a new task to the list, 
 removing a specific task from the list, and outputting all of the tasks in the list.
 
 The data structure used is a SortedVector, allowing for tasks to be sorted by deadline.
 The SortedVector holds a Shared Pointer of type Task, allowing for multiple pointers
 to access the same task.
 */

#ifndef TASKLIST_H
#define TASKLIST_H

#include "SortedVector.h"
#include "Task.h"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class TaskList {
public:
    // Constructor and Destructor
    TaskList() {};
    virtual ~TaskList() {};
    
    // Functions to interact with the list of tasks
        // Inserts a task into the sorted task list, returning the position it was inserted into
    unsigned int addTask(shared_ptr<Task> inTask) { return taskList.insert(inTask); };
        // Removes the task at the provided position from the sorted task list
    void removeTask(unsigned int pos) { taskList.remove(pos); };
        // Returns the Task pointer held at the provided position in the SortedVector
    shared_ptr<Task> taskPtrAt(unsigned int pos) { return taskList.at(pos); };
    
    // Functions to output the list of tasks stored
    void printTaskList();
    void printTaskListDetailed();
    
    // Helper Functions
    bool empty() { return taskList.size() == 0; };
    unsigned int size() { return taskList.size(); };
    
private:    
    // Sorted Vector of Shared Pointers of type Task
    SortedVector<shared_ptr<Task>, Task::TaskPtrComparator> taskList;
};

#endif
