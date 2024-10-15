#include <iostream>
#include "Schedular.h"

int main() {
    Scheduler scheduler;

    // Adding tasks with different priorities and execution times
    scheduler.addTask(new Task(1, 3, 10)); // Task ID: 1, Priority: 3, Execution Time: 10
    scheduler.addTask(new Task(2, 1, 5));  // Task ID: 2, Priority: 1, Execution Time: 5
    scheduler.addTask(new Task(3, 2, 8));  // Task ID: 3, Priority: 2, Execution Time: 8

    // Simulating the scheduler
    scheduler.schedule(3); // Time slice of 3 units

    return 0;
}
