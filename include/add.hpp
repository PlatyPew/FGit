#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Staged {
    private:
        vector<string> paths;
        string stagedFile;
    public:
        Staged();
        void addToStaged(string fileName, bool isDelete, bool isBinary);
        void printStaged();
};

class Add {
    private:
    Staged staged;

    public:
        void add();
        void add(string fileName);
};