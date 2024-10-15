#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <string>

class FileExplorer {
public:
    void listDirectory(const std::string &path, bool showHidden);
    void searchFiles(const std::string &path, const std::string &pattern);
    void navigate(const std::string &path);

private:
    bool isHiddenFile(const std::string &filename);
    bool patternMatch(const std::string &filename, const std::string &pattern);
};

#endif // FILE_EXPLORER_H
