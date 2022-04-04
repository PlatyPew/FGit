#pragma once

#include <iostream>
#include <vector>
#include <dirent.h> 

using namespace std;


class status {
    public:
        status();
        vector<string> allHomePaths;
        vector<string> AllCachePaths;
        const char* homePath;
        const char* cachePath;
        bool isFileDeleted(vector<string>, string);
        static void checkThrough(vector<string> paths);
        static bool getFileContent(std::string fileName,int isBinary, int isDelete);
        static void write(vector<string>);
    private:
}
