#include "status.hpp"
#include "defaults.hpp"
#include "diff.hpp"
#include "filehandler.hpp"

#include <algorithm>
#include <dirent.h>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>

using std::vector, std::string, std::cout, std::endl, std::pair;

Status::Status(std::string path) {
    this->path = path;
    this->flagStatus = this->insertStatusFlag();
    this->binary = isBinary();
}
int Status::getStatusFlag() {
    return this->flagStatus;
}
bool Status::isCreated() {
    bool isInCache = checkIfFileInCache(this->path);
    // RET TRUE IF NOT IN CACHE AND IN LOCAL
    if (!isInCache) {
        return Filehandler::exists(this->path);
    } else {
        return false;
    }
}
bool Status::getBinary() {
    return this->binary;
}
bool Status::isDeleted() {
    // RETURN TRUE IF IN CACCHE BUT NOT IN LOCAL
    vector<string> cachePaths = Status::getAllFilesFromDirectory(Defaults::fgitCaches);
    bool isInCache = Status::checkIfNameInVector(cachePaths, this->path);
    if (isInCache) {
        return !(Filehandler::exists(this->path));
    } else {
        return false;
    }
}
bool Status::isModified() {
    // RETURN TRUE IF IN CAHCE AND IN LOCAL AND MODIFIED
    vector<string> cachePaths = Status::getAllFilesFromDirectory(Defaults::fgitCaches);
    bool isInCache = Status::checkIfNameInVector(cachePaths, this->path);
    if (isInCache) {
        bool isInLocal = Filehandler::exists(this->path);
        if (isInLocal) {
            std::string LocalString, CacheString;
            LocalString = Filehandler::read(this->path);
            CacheString = Filehandler::read(Defaults::fgitCaches + this->path);
            return Diff::isDiff(LocalString, CacheString);
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Status::isBinary() {
    if (!Filehandler::exists(this->path)) {
        // THORW?
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
int Status::insertStatusFlag() {
    if (this->isCreated()) {
        return 1;
    } else if (this->isDeleted()) {
        return 2;
    } else if (this->isModified()) {
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
bool Status::checkIfFileInCache(std::string fileName) {
    vector<std::string> allCachePaths = Status::getAllFilesFromDirectory(Defaults::fgitCaches);
    bool inCache = Status::checkIfNameInVector(allCachePaths, fileName);
    return inCache;
}
bool Status::checkIfFileInLocal(std::string fileName) {
    vector<std::string> allHomePaths = Status::getAllFilesFromDirectory(Defaults::home);
    bool inLocal = Status::checkIfNameInVector(allHomePaths, fileName);
    return inLocal;
}
bool Status::checkIfNameInVector(std::vector<std::string> Paths, string fileName) {
    for (int i = 0; i < Paths.size(); i++) {
        if (Paths[i].compare(fileName) == 0) {
            return true;
        }
    }
    return false;
}
std::set<std::string> Status::getAllFiles() {
    std::vector<std::string> allCachePaths = Status::getAllFilesFromDirectory(Defaults::fgitCaches);
    std::vector<std::string> allHomePaths = Status::getAllFilesFromDirectory(Defaults::home);
    std::set<std::string> allFiles;
    for (int i = 0; i < allCachePaths.size(); i++) {
        bool ifInGItIgnore = checkIfNameInVector(Defaults::gitIgnore, allCachePaths[i]);
        if (ifInGItIgnore) {
            ;
        } else {
            allFiles.insert(allCachePaths[i]);
        }
    }
    for (int i = 0; i < allHomePaths.size(); i++) {
        bool ifInGItIgnore = checkIfNameInVector(Defaults::gitIgnore, allHomePaths[i]);
        if (ifInGItIgnore) {
            ;
        } else {
            allFiles.insert(allHomePaths[i]);
        }
    }
    return allFiles;
}

std::map<string, pair<bool, bool>> Status::checkThrough() {
    std::map<string, pair<bool, bool>> filesMap;
    std::vector<Status> allStatusObj = Status::getAllStatus();
    for (auto statObj = allStatusObj.begin(); statObj != allStatusObj.end(); ++statObj) {
        if (statObj->flagStatus == 2) {
            filesMap.insert(pair<string, pair<bool, bool>>(
                statObj->path, pair<bool, bool>(false, statObj->binary)));
        } else if (statObj->flagStatus == 1 || statObj->flagStatus == 3) {
            filesMap.insert(pair<string, pair<bool, bool>>(
                statObj->path, pair<bool, bool>(true, statObj->binary)));
        }
    }
    return filesMap;
}

void Status::status() {
    std::vector<Status> allStatusObj = Status::getAllStatus();
    string StatusArray[3] = {"NEW ADDED", "DELETED", "MODIFED"};
    for (int i = 1; i <= 3; i++) {
        cout << endl << "THESE FILES HAS BEEN " << StatusArray[i - 1] << endl;
        cout << "\nFile STATUS \n"
             << "=================================================================================="
                "==\n";
        for (auto itr = allStatusObj.begin(); itr != allStatusObj.end(); itr++) {
            if (itr->flagStatus == i) {
                std::cout << StatusArray[i - 1] << ":\t" << itr->path << "\t" << endl;
            }
        }
    }
}

std::vector<Status> Status::getAllStatus() {
    std::set<std::string> allPaths = Status::getAllFiles();
    std::vector<Status> allStatus;
    // readFiles(allPaths);
    for (auto it = allPaths.begin(); it != allPaths.end(); ++it) {
        Status statObj = Status(*it);
        allStatus.push_back(statObj);
    }
    return allStatus;
}
