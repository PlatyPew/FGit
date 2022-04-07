#include <dirent.h>
#include <fstream>
#include <ios>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "defaults.hpp"
#include "Filehandler.hpp"
#include "Status2.hpp"
#include "Diff.hpp"
#include <iterator>
#include <algorithm>

using namespace std;

Status::Status(std::string path){
    this->path = path;
    this->flagStatus = this->insertStatusFlag();
    this->binary = isBinary();
}
int Status::getStatusFlag(){
    return this->flagStatus;
}
bool Status::isCreated(){
    bool isInCache = checkIfFileInCache(this->path);
    // RET TRUE IF NOT IN CACHE AND IN LOCAL
    if(!isInCache){
        return Filehandler::exists(this->path);
    }
    else{
        return false;
    }
}
bool Status::isDeleted(){
    // RETURN TRUE IF IN CACCHE BUT NOT IN LOCAL
    vector<string> cachePaths = Status::getAllFilesFromDirectory(Defaults::fgitCaches);
    bool isInCache = Status::checkIfNameInVector(cachePaths,this->path);
    if(isInCache){
        return !(Filehandler::exists(this->path));
    }
    else{
        return false;
    }
}
bool Status::isModified(){
    //RETURN TRUE IF IN CAHCE AND IN LOCAL AND MODIFIED
    vector<string> cachePaths = Status::getAllFilesFromDirectory(Defaults::fgitCaches);
    bool isInCache = Status::checkIfNameInVector(cachePaths,this->path);
    if(isInCache){
        bool isInLocal = Filehandler::exists(this->path);
        if(isInLocal){
            std::string LocalString, CacheString;
            LocalString = Filehandler::read(this->path);
            CacheString = Filehandler::read(Defaults::fgitCaches+this->path);
            return Diff::isDiff(LocalString, CacheString);
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Status::isBinary() {
    if(!Filehandler::exists(this->path)){
        //THORW?
        return 0;
    }

    int c;
    string filename = this->path;
    std::ifstream ifs(filename, std::ios::binary);
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
// 1 = created , 2 = delete, 3 = modified , 0 means unstageable
int Status::insertStatusFlag(){
    if(this->isCreated()){
        return 1;
    }
    else if(this->isDeleted()){
        return 2;
    }
    else if(this->isModified()){
        return 3;
    }
    return 0;
}

vector<string> Status::getAllFilesFromDirectory(std::string subPath) {
    struct dirent* de; // Pointer for directory entry
    std::vector<string> cacheFiles;
    // opendir() returns a pointer of DIR type.
    DIR* dr = opendir(subPath.c_str());

    if (dr == NULL) // opendir returns NULL if couldn't open directory
    {
        throw("Could not open current directory");
    }

    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL)
        if (de->d_type == DT_REG) {

            cacheFiles.push_back(de->d_name);
        }
    closedir(dr);
    return cacheFiles;
}
bool Status::checkIfFileInCache(std::string fileName){
    vector <std::string> allCachePaths = Status::getAllFilesFromDirectory(Defaults::fgitCaches);
    bool inCache = Status::checkIfNameInVector(allCachePaths,fileName);
    return inCache;
}
bool Status::checkIfFileInLocal(std::string fileName){
    vector <std::string> allHomePaths = Status::getAllFilesFromDirectory(Defaults::home);
    bool inLocal = Status::checkIfNameInVector(allHomePaths,fileName);
    return inLocal;
}
bool Status::checkIfNameInVector(std::vector<std::string> Paths,string fileName){
    for (int i = 0; i < Paths.size(); i++){
        if(Paths[i].compare(fileName)==0){
            return true;
        }
    }
    return false;
}
std::set<std::string> Status::getAllFiles(){
    std::vector <std::string> allCachePaths = Status::getAllFilesFromDirectory(Defaults::fgitCaches);
    std::vector <std::string> allHomePaths = Status::getAllFilesFromDirectory(Defaults::home);
    std::set<std::string> allFiles;
    for(int i = 0; i < allCachePaths.size(); i++){
        bool ifInGItIgnore = checkIfNameInVector(Defaults::gitIgnore, allCachePaths[i]);
        if(ifInGItIgnore){
            ;
        }
        else{
            allFiles.insert(allCachePaths[i]);
        }   
    }
    for(int i = 0; i < allHomePaths.size(); i++){
        bool ifInGItIgnore = checkIfNameInVector(Defaults::gitIgnore, allHomePaths[i]);
        if(ifInGItIgnore){
            ;
        }
        else{
            allFiles.insert(allHomePaths[i]);
        }   
    }
    return allFiles;
}

void Status::printFiles(){
    std::set<std::string> x = Status::getAllFiles();
    readFiles(x);
}

template<class T>
void Status::readFiles(T allPaths){
    for (auto it = allPaths.begin(); it != allPaths.end(); ++it){
        cout << ' ' << *it;
    }
    cout << endl;
}

std::map<string, pair<bool, bool>> Status::checkThrough(){
    std::map<string, pair<bool, bool>> filesMap;
    std::set<std::string> allPaths = Status::getAllFiles();
    // readFiles(allPaths);
    for (auto it = allPaths.begin(); it != allPaths.end(); ++it){
        Status statObj = Status(*it);
        if(statObj.flagStatus == 2){
            filesMap.insert(pair<string, pair<bool, bool>>(statObj.path, pair<bool, bool>(false, statObj.binary))); 
        }
        else if(statObj.flagStatus == 1 || statObj.flagStatus == 3){
            filesMap.insert(pair<string, pair<bool, bool>>(statObj.path, pair<bool, bool>(true, statObj.binary)));   
        }
    }
    return filesMap;
}

std::map<string, pair<bool, int>> Status::checkThrough(map<string, pair<bool, int>> files) {
    std::map<string, pair<bool, int>> filesMap;
    std::set<std::string> allPaths = Status::getAllFiles();
    // readFiles(allPaths);
    for (auto it = allPaths.begin(); it != allPaths.end(); ++it){
        Status statObj = Status(*it);
        if(statObj.flagStatus == 2){
            filesMap.insert(pair<string, pair<bool, int>>(statObj.path, pair<bool, int>(false, statObj.flagStatus))); 
        }
        else if(statObj.flagStatus == 1 || statObj.flagStatus == 3){
            filesMap.insert(pair<string, pair<bool, int>>(statObj.path, pair<bool, int>(true, statObj.flagStatus)));   
        }
    }
    return filesMap;
}
    
void Status::printMap(){
    map<string, pair<bool, int>> files;
    string StatusArray[3] = {"DELETED","MODIFIED","NEWLY ADDED"};
    vector<int> StatusFlag;
    std::map<string, pair<bool, int>> stageMap = Status::checkThrough(files);
    cout << "\nFile STATUS \n" << "====================================================================================\n";
    for(int i = 1; i <=3; i++){
        cout << endl<<"THESE FILES HAS BEEN " << StatusArray[i-1] << endl;
        for (auto itr = stageMap.begin(); itr != stageMap.end(); itr++){
            if(itr->second.second == i){
                std::cout << StatusArray[i-1] <<":\t"<< itr->first<< "\t" <<endl;
            }
        }
    }
}