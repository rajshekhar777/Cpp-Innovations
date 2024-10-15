# File System Explorer (CLI Tool)

## Description
The File System Explorer is a command-line interface (CLI) tool that allows users to navigate, search, and manipulate files and directories in a file system. This tool highlights skills in file I/O operations, recursive algorithms, and working with file systems.

## Features
- **List Files and Directories:** List all files and directories in a specified path. Option to include hidden files.
- **Pattern-Based Search:** Search for files that match a specified pattern using regular expressions (similar to `grep`).
- **Navigate Directories:** Change the current working directory to a specified path.

## Requirements
- C++17 or newer
- C++ standard library support for `<filesystem>`
- A C++ compiler (e.g., g++)

## Project Structure
- `main.cpp`: The main program logic and entry point for the CLI tool.
- `FileExplorer.h`: Header file with function declarations for file operations.
- `FileExplorer.cpp`: Implementation file containing the logic for listing, searching, and navigating files.

## Compilation
To compile the project, open a terminal and navigate to the project directory. Run the following command:

```bash
g++ main.cpp FileExplorer.cpp -o file_explorer -std=c++17

Run the compiled program using the following command:
./file_explorer <command> <arguments>

Commands
List Files and Directories:
./file_explorer list <path> [-a]
ex-
 ./file_explorer list /path/to/directory -a


Search Files:
./file_explorer search <path> <pattern>
ex-
./file_explorer search /path/to/directory ".*\.txt"


Navigate Directories:
./file_explorer navigate <path>
ex-
./file_explorer navigate /path/to/directory


