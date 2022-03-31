#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Staged {
    private:
        vector<string> paths;
    public:
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