/*******************/
/** COMMAND CLASS **/
/*******************/
/*
 Command is a data container struct/class that tracks a single (reversible) command 
 invoked by the user—i.e., ADD, COMPLETE, and REMOVE. It is meant to aid in the 
 process of undoing and redoing actions. Command contains a command type and the 
 specific task affected by the invoked command.
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <memory>
#include "Task.h"
using namespace std;

class Command {
public:
    // Constructor and Destructor
    Command () {};
    Command(string inCommandType, unsigned int inPos, shared_ptr<Task> taskAffected) :
        cmdType(inCommandType), posAffected(inPos), taskAffected(taskAffected) {};
    virtual ~Command() {};
    
    // Setters and Getters
    void setCommandType(string inCommandType) { cmdType = inCommandType; };
    void setPosAffected(unsigned int inPos) { posAffected = inPos; };
    void setTaskAffected(shared_ptr<Task> inTask) { taskAffected = inTask; };
    string getCommandType() { return cmdType; };
    unsigned int getPosAffected() { return posAffected; };
    shared_ptr<Task> getTaskAffected() { return taskAffected; };

private:
    string cmdType;
    unsigned int posAffected;
    shared_ptr<Task> taskAffected;
};

#endif
