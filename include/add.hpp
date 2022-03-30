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
        Staged(string stagedFile);
        void addToStaged(string fileName);
        void printStaged();
};


class Add {
    private:
    Staged staged;

    public:
        void add();
        void add(string fileName);
};