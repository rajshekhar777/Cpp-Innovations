#ifndef TASK_H
#define TASK_H

#include <iostream>

class Task {
public:
    int id;                 // Task ID
    int priority;          // Priority of the task (higher value indicates higher priority)
    int executionTime;     // Time required to execute the task
    int remainingTime;      // Remaining time for the task

    Task(int id, int priority, int executionTime)
        : id(id), priority(priority), executionTime(executionTime), remainingTime(executionTime) {}

    void execute(int time) {
        if (remainingTime > time) {
            remainingTime -= time;
        } else {
            remainingTime = 0;
        }
    }

    bool isCompleted() const {
        return remainingTime == 0;
    }
};

#endif // TASK_H
