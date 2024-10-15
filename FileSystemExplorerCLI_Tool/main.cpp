#include <iostream>
#include <string>
#include "FileExplorer.h"

int main(int argc, char *argv[]) {
    FileExplorer explorer;

    if (argc < 2) {
        std::cout << "Usage: ./file_explorer <command> <arguments>\n";
        std::cout << "Commands:\n";
        std::cout << "  list <path> [-a]   : List files and directories. Use -a to include hidden files.\n";
        std::cout << "  search <path> <pattern>   : Search files matching the pattern.\n";
        std::cout << "  navigate <path>    : Navigate to the specified directory.\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "list" && argc >= 3) {
        std::string path = argv[2];
        bool showHidden = (argc == 4 && std::string(argv[3]) == "-a");
        explorer.listDirectory(path, showHidden);
    } 
    else if (command == "search" && argc == 4) {
        std::string path = argv[2];
        std::string pattern = argv[3];
        explorer.searchFiles(path, pattern);
    }
    else if (command == "navigate" && argc == 3) {
        std::string path = argv[2];
        explorer.navigate(path);
    } 
    else {
        std::cout << "Invalid command or arguments. Use './file_explorer help' for more info.\n";
    }

    return 0;
}
