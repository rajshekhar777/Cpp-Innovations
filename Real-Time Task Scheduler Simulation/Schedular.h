#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <queue>
#include "Task.h"

class Scheduler {
private:
    std::priority_queue<Task*, std::vector<Task*>, 
        bool(*)(Task*, Task*)> taskQueue;

public:
    Scheduler();
    void addTask(Task* task);
    void schedule(int timeSlice);
    void handlePriorityInversion();
};

#endif // SCHEDULER_H
