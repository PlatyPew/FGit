#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Staged {
  private:
    vector<string> paths;
    string stagedFile;
    vector<string> cachePath;

  public:
    Staged();
    void addToStaged(string fileName, bool isDelete, bool isBinary);
    void printStaged();
    static string readFileIntoString(const string& path);
    static std::vector<string> getAllFilesFromDirectory(const char*);
    static int ifModifiedOrAdded(string);
    
};

class Add {
  private:
    Staged staged;
    static bool checkIfFileInLocal(std::string);
    

  public:
    void add();
    void add(string fileName);
    void setBinary();
    static bool checkIfBinary(string);
    static bool updateStage(std::string fileName);
    static void write(vector<string>);
    // bool checkIfFileStagable(string fileName);
    
};
