
#pragma once

#include "Task.h"
#include "Person.h"

/**
 * @brief Class managing tasks assigned to multiple persons.
 */
class TaskManager {
private:
    /**
     * @brief Maximum number of persons the TaskManager can handle.
     */
    static const int MAX_PERSONS = 10;
    static const int MAX_PRIORITY = 100;
    int current_persons;
    int recent_id;
    Person persons[MAX_PERSONS];

    int findMaxTask(const SortedList<Task>::ConstIterator *tasks) const;

    bool isWentOverAllTasks(const SortedList<Task>::ConstIterator *tasks) const;

    class BumpTaskPriorityByType {
        TaskType type;
        int priority;

    public:
        BumpTaskPriorityByType(const TaskType &type, int priority): type(type), priority(priority) {
        }

        Task operator()(const Task &task) {
            if (task.getType() == type) {
                Task toAdd(task.getPriority() + priority > MAX_PRIORITY
                               ? MAX_PRIORITY
                               : task.getPriority() + priority,
                           task.getType(),
                           task.getDescription());
                toAdd.setId(task.getId());
                return toAdd;
            }
            return task;
        }
    };

public:
    /**
     * @brief Default constructor to create a TaskManager object.
     *
     * Note - you may add =default if needed.
     */
    TaskManager();

    /**
     * @brief Deleted copy constructor to prevent copying of TaskManager objects.
     */
    TaskManager(const TaskManager &other) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent assignment of TaskManager objects.
     */
    TaskManager &operator=(const TaskManager &other) = delete;

    /**
     * @brief Assigns a task to a person.
     *
     * @param personName The name of the person to whom the task will be assigned.
     * @param task The task to be assigned.
     */
    void assignTask(const string &personName, const Task &task);

    /**
     * @brief Completes the highest priority task assigned to a person.
     *
     * @param personName The name of the person who will complete the task.
     */
    void completeTask(const string &personName);

    /**
     * @brief Bumps the priority of all tasks of a specific type.
     *
     * @param type The type of tasks whose priority will be bumped.
     * @param priority The amount by which the priority will be increased.
     */
    void bumpPriorityByType(TaskType type, int priority);

    /**
     * @brief Prints all employees and their tasks.
     */
    void printAllEmployees() const;

    /**
     * @brief Prints all tasks of a specific type.
     *
     * @param type The type of tasks to be printed.
     */
    void printTasksByType(TaskType type) const;

    /**
     * @brief Prints all tasks assigned to all employees.
     */
    void printAllTasks() const;
};
