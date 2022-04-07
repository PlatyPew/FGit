#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>

class Status {
  private:
    std::string path;
    int flagStatus;
    bool binary;

    bool isCreated();
    bool isModified();
    bool isDeleted();
    bool isBinary();
    int insertStatusFlag();

  public:
    Status(std::string path);
    int getState(); // created: 0, modified: 1, deleted: 2
    bool getBinary();
    bool checkIfFileInLocal(std::string fileName);
    bool checkIfFileInCache(std::string fileName);
    static bool checkIfNameInVector(std::vector<std::string> Paths,std::string fileName);
    static std::vector<std::string> getAllFilesFromDirectory(std::string subPath);
    static std::map<std::string, std::pair<bool, bool>> getCommitableFiles();
    static std::vector<std::string> getFiles(); // This will get a list of files in the cache and workspace and merge them together
    static std::set<std::string> getAllFiles();
    static void status();
    static void printFiles();
    template<class T> static void readFiles(T);
    static std::map<std::string, std::pair<bool, bool>> checkThrough();
    static std::map<std::string, std::pair<bool, int>> checkThrough( std::map<std::string, std::pair<bool, int>> files);
    int getStatusFlag();
    static void printStatus(); //Print status
    static void printMap();// Used to check if map is working
    static std::vector<Status> getAllStatus(); 
    
};