#include "TaskManager.h"


TaskManager::TaskManager() : current_persons(0), recent_id(0) {
}

/**
 * @brief Assigns a task to a person.
 *
 * @param personName The name of the person to whom the task will be assigned.
 * @param task The task to be assigned.
 */
void TaskManager::assignTask(const string &personName, const Task &task) {
     Task toAdd(task);

     for (int i = 0; i < this->current_persons; i++) {
          if (persons[i].getName() == personName) {
               toAdd.setId(recent_id++);
               persons[i].assignTask(toAdd);
               return;
          }
     }
     if (current_persons == MAX_PERSONS) {
          throw std::runtime_error("");
     }
     persons[current_persons] = Person(personName);
     toAdd.setId(recent_id++);
     persons[current_persons++].assignTask(toAdd);
}

/**
 * @brief Completes the highest priority task assigned to a person.
 *
 * @param personName The name of the person who will complete the task.
 */
void TaskManager::completeTask(const string &personName) {
     for (int i = 0; i < current_persons; i++) {
          if (persons[i].getName() == personName) {
               persons[i].completeTask();
          }
     }
}

/**
 * @brief Bumps the priority of all tasks of a specific type.
 *
 * @param type The type of tasks whose priority will be bumped.
 * @param priority The amount by which the priority will be increased.
 */


void TaskManager::bumpPriorityByType(TaskType type, int priority) {
     if (priority <= 0) {
          return;
     }

     SortedList<Task> tasksToBump;

     for (int i = 0; i < current_persons; i++) {
          BumpTaskPriorityByType bumpTask(type, priority);

          tasksToBump = persons[i].getTasks().apply(bumpTask);

          persons[i].setTasks(tasksToBump);
     }
}

/**
 * @brief Prints all employees and their tasks.
 */
void TaskManager::printAllEmployees() const {
     for (int i = 0; i < current_persons; i++) {
          std::cout << persons[i] << std::endl;
     }
}

/**
 * @brief Prints all tasks of a specific type.
 *
 * @param type The type of tasks to be printed.
 */
void TaskManager::printTasksByType(TaskType type) const {
     TaskManager toPrint;

     for (int i = 0; i < current_persons; i++) {
          toPrint.persons[i].setTasks(
               persons[i].getTasks().filter([type](const Task &task) {
                    return task.getType() == type;
               }));
     }
     toPrint.printAllTasks();
}

/**
 * @brief Prints all tasks assigned to all employees.
 */
void TaskManager::printAllTasks() const {
     SortedList<Task>::ConstIterator tasks[MAX_PERSONS];

     for (int i = 0; i < MAX_PERSONS; i++) {
          tasks[i] = persons[i].getTasks().begin();
     }

     while (!isWentOverAllTasks(tasks)) {
          int maxInd = findMaxTask(tasks);

          std::cout << *tasks[maxInd] << std::endl;

          ++tasks[maxInd];
     }
}

int TaskManager::findMaxTask(const SortedList<Task>::ConstIterator *tasks) const {
     int maxInd = -1;
     for (int i = 0; i < MAX_PERSONS; i++) {
          if (tasks[i] != persons[i].getTasks().end()) {
               if (maxInd == -1 || *tasks[i] > *tasks[maxInd]) {
                    maxInd = i;
               }
          }
     }

     return maxInd;
}

bool TaskManager::isWentOverAllTasks(const SortedList<Task>::ConstIterator *tasks) const {
     for (int i = 0; i < MAX_PERSONS; i++) {
          if (tasks[i] != persons[i].getTasks().end()) {
               return false;
          }
     }
     return true;
}
