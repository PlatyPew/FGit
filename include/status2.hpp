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
    bool checkIfFileInLocal(std::string fileName);
    bool checkIfFileInCache(std::string fileName);
    static bool checkIfNameInVector(std::vector<std::string> Paths,std::string fileName);
    static std::vector<std::string> getAllFilesFromDirectory(std::string subPath);
    static std::set<std::string> getAllFiles();// This will get a list of files in the cache and workspace and merge them together
  public:
    Status(std::string path);
    bool getBinary();
    static void status();//Print status
    static std::map<std::string, std::pair<bool, bool>> checkThrough();
    int getStatusFlag();
    static std::vector<Status> getAllStatus(); 
    
};