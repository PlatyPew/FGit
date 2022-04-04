#include "status.hpp"
#include "add.hpp"
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

status::status() {
    this->homePath = ".";
    this->cachePath = "../Fake-Git/.fgit/caches";
    allHomePaths = Staged::getAllFilesFromDirectory(homePath);
    AllCachePaths = Staged::getAllFilesFromDirectory(cachePath);
}
// bool status::isFileDeleted(vector<string> paths, string filePath){
//     for(int i = 0; i<paths.size(); i++){
//         //If Match return true, has not been deleted
//         if(paths[i].compare(filePath)== 0){
//             return false;
//         }
//     }
//     //No match, means has been deleted
//     return true;
// }

void status::checkThrough(vector<string> paths) {
    for (int i = 0; i < paths.size(); i++) {
        ifstream myfile;
        myfile.open(paths[i]);
        if (myfile) {
            cout << endl << paths[i] << " file exists!!! \n";

        } else {
            getFileContent(paths[i], 1, 1);
            cout << endl << paths[i] << "file doesn't exist!!!\n";
        }
    }
}

void status::write(vector<string> v) {
    ofstream file;
    file.open("staged");
    for (int i = 0; i < v.size(); ++i) {
        file << v[i] << endl;
    }
    file.close();
}

bool status::getFileContent(std::string fileName, int isBinary, int isDelete) {
    int binary = 0;
    string inputform = fileName + "," + to_string(binary) + "," + "1";
    string inputform2 = fileName + "," + to_string(binary) + "," + "0";
    vector<string> x;
    std::ifstream file("staged");
    std::string str;
    while (std::getline(file, str)) {
        if (str.compare(inputform) == 0 || str.compare(inputform2) == 0) {
            str = inputform;
        }
        x.push_back(str);
    }
    write(x);
    return true;
    ;
}
