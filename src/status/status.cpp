#include <dirent.h>
#include <fstream>
#include <ios>
#include <iostream>
#include <vector>
#include <map>
#include "defaults.hpp"
#include "status.hpp"
#include "add.hpp"
#include <iterator>
#include <algorithm>

using namespace std;

status::status() {
    allHomePaths = Staged::getAllFilesFromDirectory(Defaults::home.c_str());
    AllCachePaths = Staged::getAllFilesFromDirectory(Defaults::fgitCaches.c_str());
}
void status::printMap(std::map<string, pair<bool, bool>> stageMap){
    cout << "\nFile Staged! \n";
    for (auto itr = stageMap.begin(); itr != stageMap.end(); itr++)
            std::cout <<endl<< itr->first<<endl;
}
void status::printMap(){
    map<string, pair<bool, int>> files;
    string status[3] = {"DELETED","MODIFIED","NEWLY ADDED"};
    vector<int> statusFlag;
    std::map<string, pair<bool, int>> stageMap = status::checkThrough(files);
    cout << "\nFile STATUS \n" << "====================================================================================\n";
    for(int i = 1; i <=3; i++){
        cout << endl<<"THESE FILES HAS BEEN " << status[i-1] << endl;
        for (auto itr = stageMap.begin(); itr != stageMap.end(); itr++){
            if(itr->second.second == i){
                std::cout << status[i-1] <<":\t"<< itr->first<< "\t" <<endl;
            }
        }

    }
    

    
}
bool status::checkIfItemInMap(std::map<string, pair<bool, bool>> stageMap,string fileName){
    if(stageMap.count(fileName) > 0){
        return true;
    }
    else{
        return false;
    }
}
std::map<string, pair<bool, bool>> status::checkThrough() {
    // Cache check against local
    map<string, pair<bool, bool>> files;
    vector<string> paths = Staged::getAllFilesFromDirectory(Defaults::fgitCaches.c_str());
    for (int i = 0; i < paths.size(); i++) {
        bool isDelete = isFileDelete(paths[i]);
        if(isDelete){
            std::string filePath = Defaults::fgitCaches + paths[i];
            bool isBinary = Add::checkIfBinary(filePath);
            files.insert(pair<string, pair<bool, bool>>(paths[i], pair<bool, bool>(isDelete, isBinary)));   
        }
    }
    // local against cache
    vector<string> currentPaths = Staged::getAllFilesFromDirectory(Defaults::home.c_str());
    for (int i = 0; i < currentPaths.size(); i++){
        int isModifiedOrAdded = Staged::ifModifiedOrAdded(currentPaths[i]);
        bool isInGitIGnore = checkIfNameInVector(Defaults::gitIgnore,currentPaths[i]);
        if(isModifiedOrAdded != 0 && !isInGitIGnore){
            bool isBinary = status::checkIfBinary(currentPaths[i]);
            files.insert(pair<string, pair<bool, bool>>(currentPaths[i], pair<bool, bool>(false, isBinary))); 
        }
    }
    // printMap(files);
    return files;
}

std::map<string, pair<bool, int>> status::checkThrough(map<string, pair<bool, int>> files) {
    // Cache check against local
    vector<string> paths = Staged::getAllFilesFromDirectory(Defaults::fgitCaches.c_str());
    for (int i = 0; i < paths.size(); i++) {
        bool isDelete = isFileDelete(paths[i]);
        if(isDelete){
            std::string filePath = Defaults::fgitCaches + paths[i];
            files.insert(pair<string, pair<bool, int>>(paths[i], pair<bool, int>(isDelete, 1)));   
        }
    }
    // local against cache
    vector<string> currentPaths = Staged::getAllFilesFromDirectory(Defaults::home.c_str());
    for (int i = 0; i < currentPaths.size(); i++){
        int isModifiedOrAdded = Staged::ifModifiedOrAdded(currentPaths[i]);
        bool isInGitIGnore = checkIfNameInVector(Defaults::gitIgnore,currentPaths[i]);
        if(isModifiedOrAdded != 0 && !isInGitIGnore){
            files.insert(pair<string, pair<bool, int>>(currentPaths[i], pair<bool, int>(false, isModifiedOrAdded))); 
        }
    }
    // printMap(files);
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

// void addModifiedAndNewFile(){
//     vector<string> paths = Staged::getAllFilesFromDirectory(Defaults::fgitCaches.c_str());
//     for
//     Staged::ifModifiedOrAdded(); 
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
    std::ifstream ifs(fileName, std::ios::binary);
    if (ifs.fail()) {
        throw "file does not exist";
    }
    while ((c = ifs.get()) != EOF && c <= 127)
        ;
    if (c == EOF) {
        return false;
    } else {
        return true;
    }
}

bool status::checkIfFileInLocal(std::string fileName){
    vector <std::string> allHomePaths = Staged::getAllFilesFromDirectory(Defaults::home.c_str());
    bool inLocal = status::checkIfNameInVector(allHomePaths,fileName);
    return inLocal;
}

bool status::checkIfFileStagable(string fileName){
    return status::checkIfItemInMap(status::checkThrough() , fileName);
}
