#include <dirent.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "defaults.hpp"
#include "status.hpp"
#include "add.hpp"

using namespace std;

status::status() {
    allHomePaths = Staged::getAllFilesFromDirectory(Defaults::home.c_str());
    AllCachePaths = Staged::getAllFilesFromDirectory(Defaults::fgitCaches.c_str());
}

std::map<string, pair<bool, bool>> status::checkThrough() {
    map<string, pair<bool, bool>> files;
    vector<string> paths = Staged::getAllFilesFromDirectory(Defaults::fgitCaches.c_str());
    for (int i = 0; i < paths.size(); i++) {
        bool isDelete = isFileDelete(paths[i]);
        if(isDelete){
            std::string filePath = Defaults::fgitCaches + paths[i];
            bool isBinary = Add::checkIfBinary(filePath);
            cout << endl << filePath << " HAS BEEN ADDED \n";
            files.insert(pair<string, pair<bool, bool>>(paths[i], pair<bool, bool>(isDelete, isBinary)));   
        }
    }
    // cout << "\n============================================\n";
    vector<string> currentPaths = Staged::getAllFilesFromDirectory(Defaults::home.c_str());
    for (int i = 0; i < currentPaths.size(); i++){
        bool isModifiedOrAdded = Staged::ifModifiedOrAdded(currentPaths[i]);
        bool isInGitIGnore = checkIfNameInVector(Defaults::gitIgnore,currentPaths[i]);
        if(isModifiedOrAdded && !isInGitIGnore){
            bool isBinary = status::checkIfBinary(currentPaths[i]);
            cout << endl << currentPaths[i] << " HAS BEEN ADDED \n";
            files.insert(pair<string, pair<bool, bool>>(currentPaths[i], pair<bool, bool>(false, isBinary))); 
        }
    }
    return files;
}

bool status::isFileDelete(std::string fileName){
    ifstream myfile;
        myfile.open(fileName);
        if (myfile) {
            return false;
        } else {
            return true;
        }
}
// void addModifiedAndNewFile(){
//     vector<string> paths = Staged::getAllFilesFromDirectory(Defaults::fgitCaches.c_str());
//     for
//     Staged::ifModifiedOrAdded(); 
// }

void status::write(vector<string> v) {
    ofstream file;
    file.open("staged");
    for (int i = 0; i < v.size(); ++i) {
        file << v[i] << endl;
    }
    file.close();
}

// bool status::getFileContent(std::string fileName, int isBinary, int isDelete) {
//     int binary = 0;
//     string inputform = fileName + "," + to_string(binary) + "," + "1";
//     string inputform2 = fileName + "," + to_string(binary) + "," + "0";
//     vector<string> x;
//     std::ifstream file("staged");
//     std::string str;
//     while (std::getline(file, str)) {
//         if (str.compare(inputform) == 0 || str.compare(inputform2) == 0) {
//             str = inputform;
//         }
//         x.push_back(str);
//     }
//     write(x);
//     return true;
// }

bool status::checkIfNameInVector(vector<std::string> gitIgnore,string fileName){
    for (int i = 0; i < gitIgnore.size(); i++){
        if(gitIgnore[i].compare(fileName)==0){
            return true;
        }
    }
    return false;
}

bool status::checkIfBinary(string fileName) {
    int c;
    std::ifstream ifs(fileName);
    if (ifs.fail()) {
        return 0;
    }
    while ((c = ifs.get()) != EOF && c <= 127)
        ;
    if (c == EOF) {
        return true;
    } else {
        return false;
    }
}

bool status::checkIfFileInLocal(std::string fileName){
    vector <std::string> allHomePaths = Staged::getAllFilesFromDirectory(Defaults::home.c_str());
    bool inLocal = status::checkIfNameInVector(allHomePaths,fileName);
    return inLocal;
}