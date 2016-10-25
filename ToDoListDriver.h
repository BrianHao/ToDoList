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

#ifndef TODOLIST_DRIVER_H
#define TODOLIST_DRIVER_H
#include "TaskList.h"
using namespace std;

class ToDoListDriver {
public:
    // Constructor and Destructor
    ToDoListDriver() {};
    virtual ~ToDoListDriver() {};
    
    // Functions to interact with the TaskLists
    int addOutstandingTask(Task *inTask) { return outstandingTasks.addTask(inTask); };
    int addOutstandingTask(string &inSaveString) { return outstandingTasks.addTask(inSaveString); };
    string removeOutstandingTask(unsigned int pos) { return outstandingTasks.removeTask(pos); };
    int completeOutstandingTask(unsigned int pos);
    
    // Functions to output the list of tasks stored
    void printOutstandingTaskList() { outstandingTasks.printTaskList(); };
    void printOutstandingTaskListDetailed() { outstandingTasks.printTaskListDetailed(); };
    void printCompletedTaskList() { completedTasks.printTaskList(); };
    void printCompletedTaskListDetailed() { completedTasks.printTaskListDetailed(); };
    
    
private:
    // A TaskList that manages currently incomplete tasks.
    TaskList outstandingTasks;
    // A TaskList that holds all completed tasks.
    TaskList completedTasks;
};

#endif
