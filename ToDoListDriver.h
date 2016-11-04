/*********************/
/** TODOLIST_DRIVER **/
/*********************/
/*
 ToDoListDriver provides an interface over two TaskLists — one that represents the outstanding
 tasks and another that represents the completed tasks. It provides functionality such as 
 creating a new outstanding task, removing a specific outstanding task, marking a specific 
 outstanding task as complete, and outputting the outstanding/completed tasks in 
 non-detailed/detailed manners.
 */

#ifndef TODOLIST_DRIVER_H
#define TODOLIST_DRIVER_H

#include <memory>
#include "TaskList.h"
#include "Task.h"
using namespace std;

class ToDoListDriver {
public:
    // Constructor and Destructor
    ToDoListDriver() {};
    virtual ~ToDoListDriver() {};
    
    // Functions to interact with the TaskLists
        // Adds a new task into the Outstanding Tasks list, returning the position it was inserted into
    unsigned int addOutstandingTask(shared_ptr<Task> inTask) { return outstandingTasks.addTask(inTask); };
        // Removes the Outstanding Task at provided position
    void removeOutstandingTask(unsigned int pos) { outstandingTasks.removeTask(pos); };
        // Removes the Complete Task at provided position
    void removeCompletedTask(unsigned int pos) { completedTasks.removeTask(pos); };
        // Moves the Outstanding Task at the provided position into the Completed Tasks List
    unsigned int completeOutstandingTask(unsigned int pos);
    
    // Functions to output the list of tasks stored
    void printOutstandingTaskList() { outstandingTasks.printTaskList(); };
    void printOutstandingTaskListDetailed() { outstandingTasks.printTaskListDetailed(); };
    void printCompletedTaskList() { completedTasks.printTaskList(); };
    void printCompletedTaskListDetailed() { completedTasks.printTaskListDetailed(); };
    
    // Helper Functions
        // Returns if the tasklist is empty
    bool outstandingTasksIsEmpty() { return outstandingTasks.empty(); };
    bool completedTasksIsEmpty() { return completedTasks.empty(); };
        // Returns the task pointer at the provided position
    shared_ptr<Task> outstandingTaskAt(unsigned int pos) { return outstandingTasks.taskPtrAt(pos); };
    shared_ptr<Task> completedTaskAt(unsigned int pos) { return completedTasks.taskPtrAt(pos); };
        // Returns task list size
    int outstandingTaskListSize() { return outstandingTasks.size(); };
    int completedTaskListSize() { return completedTasks.size(); };
    
private:
    // A TaskList that manages currently incomplete tasks.
    TaskList outstandingTasks;
    // A TaskList that holds all completed tasks.
    TaskList completedTasks;
};

#endif
