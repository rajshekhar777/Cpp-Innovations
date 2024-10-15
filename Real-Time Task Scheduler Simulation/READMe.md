# Real-Time Task Scheduler Simulation

## Description
This project simulates a real-time task scheduler using C++. The scheduler manages processes with different priorities and execution times, highlighting key concepts in real-time systems.

## Features
- **Task Management:** Add tasks with varying priorities and execution times.
- **Scheduling:** Simulate task execution based on priority using a preemptive scheduling approach.
- **Priority Inversion Handling:** Placeholder for future implementation of priority inversion handling.

## Requirements
- C++11 or newer
- A C++ compiler (e.g., g++)

## Project Structure
- `main.cpp`: The main program logic and entry point for the simulation.
- `Task.h`: Header file for task management.
- `Scheduler.h`: Header file for the task scheduler.
- `Scheduler.cpp`: Implementation file for the task scheduler.

## Compilation
To compile the project, open a terminal and navigate to the project directory. Run the following command:

```bash
g++ main.cpp Scheduler.cpp -o task_scheduler -std=c++11

