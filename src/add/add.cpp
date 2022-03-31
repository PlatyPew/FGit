#include "add.hpp"

#include "commit.hpp"

#include <iostream>

using namespace std;

void Add::add(){
    cout << "Please input filename" << endl;
}

void Add::add(string fileName){
    cout << "constructor with filename" << endl;
    this->staged.addToStaged(fileName);
}

void Staged::addToStaged(string fileName){
    this->paths.push_back(fileName);
    this->printStaged();
}

void Staged::printStaged(){
    for(string path: paths)
        cout << path << " ";
}