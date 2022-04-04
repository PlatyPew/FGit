#pragma once

#include <dirent.h>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class status {
  public:
    
    status();
    static map<string, pair<bool, bool>> files;
    vector<string> allHomePaths;
    vector<string> AllCachePaths;
    const char* homePath;
    const char* cachePath;
    static bool isFileDeleted(vector<string>, string);
    static std::map<string, pair<bool, bool>> checkThrough();
    static bool getFileContent(std::string fileName, int isBinary, int isDelete);
    static void write(vector<string>);
    static bool isFileDelete(std::string fileName);
    static bool checkIfNameInVector(vector<std::string> gitIgnore,string fileName);
    static bool checkIfBinary(string fileName);
    static bool checkIfFileInLocal(string fileName);
};
