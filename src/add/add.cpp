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
    this->staged.addToStaged(fileName);
}

Staged::Staged(){
    this->stagedFile = "sample.txt";
}

Staged::Staged(string stagedFile){
    this->stagedFile = stagedFile;
}

void Staged::addToStaged(string fileName){
    ofstream fout;
    this->paths.push_back(fileName);
    
    fout.open(this->stagedFile, ios::app);
    fout << fileName << endl;
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