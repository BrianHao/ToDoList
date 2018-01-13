# To-Do List Application
Brian Hao

This is a task-listing application that allows users to track of their daily tasks.

### Types of Tasks

The To-Do List allows for the creation and tracking of four different types.

#### Generic Tasks
Generic Tasks are the most basic types of tasks. They contain:

* A deadline

* A task description

#### Shopping Tasks
Shopping Tasks contain the following:

* A deadline

* A task description

* A shopping list of items to be purchased

#### Event Tasks
Event Tasks contain the following:

* A deadline

* A task description

* The event's location

* The event's time

#### Homework Tasks
Homework Tasks contain the following:

* A deadline

* A task description

* The associated class subject


### Commands available to the user
The following are the actions available to the user when using the To-Do List:

##### ADD
This command creates a new task. All newly created tasks are considered “outstanding” 
to start. The user specifies the task’s type, deadline, and description. If a specialized 
task requires additional information, the user provides that as well.

##### PRINT
This command displays all of the outstanding tasks in order of deadline. If multiple 
tasks are due the same number of days into the future, they are displayed in alphabetical 
order of description. Each task is printed on its own line, beginning with its position in 
the overall list, followed by its deadline, type, and description.

##### DETAILED
This command does everything that the PRINT command does and also displays any specialized 
task information.

##### COMPLETE
This command marks a specific outstanding task as complete. The user specifies the task number 
to mark as complete, as that task appears in the lists of the PRINT/DETAILED commands.

##### COMPLETED
This command displays all of the completed tasks. It follows the same format as the PRINT command.

##### UNDO
This command undoes the last ADD, REMOVE, or COMPLETE action. The user can undo actions multiple 
times, so long as there are actions left to undo.

##### REDO
This command redoes an action that was previously undone. Note that if an action is undone, 
but then the user subsequently performs an ADD/COMPLETE/REMOVE action, the user will no longer 
be able to redo the undone action.

##### SAVE
This command saves all of the outstanding tasks to a file. The user specifies the name of the 
file to create. If a file with that name already exists, overwrite it.

##### LOAD
This command loads all of the tasks from a file as outstanding tasks.

##### EXIT
This command will exit the program.

##### HELP
This command displays all of the available commands and their descriptions.


### Tasks File Format

A tasks file contains a single task on every line. Each individual component of a task’s data is
separated by a pipe character (“|”) and is ordered as follows—type, deadline, description, and 
any additional specialized task information. Generic tasks, shopping tasks, events, and homework 
tasks follow the formats, respectively:

`G|4|Put away fans, bring out space heaters`

`S|3|Shopping Day @ Manhattan Mall|Socks|3 Sweaters (Blue, Green & Red)|Dessert Boots`

`E|5|Networking Event|Hudson Terrace|8:00PM`

`H|6|Homework|AFPRL 100`

## Compilation Instructions
Compile your code with:

`$ make`

Execute using:

`./ToDoList`
