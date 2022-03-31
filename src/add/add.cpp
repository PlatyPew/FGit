#include "add.hpp"
#include "commit.hpp"
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

void Add::add(){
    cout << "Please input filename" << endl;
}

void Add::add(string fileName){
    cout << "constructor with filename " << fileName << endl;

    bool isDelete = 0;
    bool isBinary = 0;

    // TODO: Add git status code here , get values for isDelete and isBinary
    
    this->staged.addToStaged(fileName, isDelete, isBinary);
}

Staged::Staged(){
    this->stagedFile = "staged";
}

void Staged::addToStaged(string fileName, bool isDelete, bool isBinary){
    ofstream fout;
    this->paths.push_back(fileName);
    
    fout.open(this->stagedFile, ios::app);
    fout << fileName << "," << isDelete << "," << isBinary << endl;
    fout.close();

    this->printStaged();
   
}

void Staged::printStaged(){
    ifstream fin;
    string line;

    fin.open(this->stagedFile);
    while(fin) {
        getline(fin, line);
        if (line.compare("") !=0 )
            cout << line << " Staged" << endl;
    }

    fin.close();
}