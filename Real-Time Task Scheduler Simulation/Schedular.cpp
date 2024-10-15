#include "Schedular.h"

// Comparison function for priority queue
bool compareTasks(Task* t1, Task* t2) {
    return t1->priority < t2->priority;
}

Scheduler::Scheduler() : taskQueue(compareTasks) {}

void Scheduler::addTask(Task* task) {
    taskQueue.push(task);
}

void Scheduler::schedule(int timeSlice) {
    while (!taskQueue.empty()) {
        Task* currentTask = taskQueue.top();
        taskQueue.pop();

        std::cout << "Executing Task ID: " << currentTask->id 
                  << " with Priority: " << currentTask->priority << std::endl;

        currentTask->execute(timeSlice);

        if (!currentTask->isCompleted()) {
            taskQueue.push(currentTask); // Re-add the task if not completed
        } else {
            std::cout << "Task ID: " << currentTask->id << " completed." << std::endl;
            delete currentTask; // Free memory for completed task
        }
    }
}

void Scheduler::handlePriorityInversion() {
    // Implement priority inversion handling logic if necessary
    // Placeholder for future implementation
}
