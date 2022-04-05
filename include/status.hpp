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
    static std::map<string, pair<bool, int>> checkThrough(map<string, pair<bool, int>> files);
    static bool isFileDelete(std::string fileName);
    static bool checkIfNameInVector(vector<std::string> gitIgnore,string fileName);
    static bool checkIfBinary(string fileName);
    //Print all trackable map
    static void printMap();
    //Print out any map.
    static void printMap(std::map<string, pair<bool, bool>> stageMap);
    static bool checkIfItemInMap(std::map<string, pair<bool, bool>>,string);
    static bool checkIfFileStagable(string fileName);
    static bool checkIfFileInLocal(string fileName);
};
