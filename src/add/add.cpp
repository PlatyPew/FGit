
#include "add.hpp"
#include "commit.hpp"
#include "diff.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <dirent.h> 

using namespace std;

void Add::add(){
    cout << "Please input filename" << endl;
}


void Add::add(string fileName){
    cout << "constructor with filename " << fileName << endl;
    vector<string> cachePath = Staged::getAllFilesFromDirectory("../Fake-Git/.fgit/caches");
    bool isDelete = false;
    bool isBinary = checkIfBinary(fileName);
    bool isStageable = Staged::ifStageable(cachePath,fileName);
    
    // TODO: Add git status code here , get values for isDelete and isBinary
    // TODO: Implement Daryl's helper function for the isStageable
    
    if (isStageable){
        this->staged.addToStaged(fileName, isDelete, isBinary);
        // this->staged.printStaged();
    }
        
    else {
        cout << "Nothing to be staged";
    }
}
bool Add::checkIfBinary(string fileName){
    int c;
    std::ifstream ifs(fileName);
    if (ifs.fail()) {
        return 0;
    }
    while ((c = ifs.get()) != EOF && c <= 127)
        ;
    if (c == EOF) {
        return true;
    }
    else {
        return false;
    }
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


vector<string>  Staged::getAllFilesFromDirectory(const char * subPath)
{
    struct dirent *de;  // Pointer for directory entry
    std::vector<string> cacheFiles;
    // opendir() returns a pointer of DIR type. 
    DIR *dr = opendir(subPath);

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
    }
  
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL)
    if (de->d_type == DT_REG)
    {
        
        cacheFiles.push_back(de->d_name);
        printf("%s\n", de->d_name);
    }
    closedir(dr);
    return cacheFiles;
}

bool Staged::ifStageable(std::vector<string> FgitPaths,string filePath){
    string CachePath = "";
    bool isExist = false;
    string fgitCachePath = "../Fake-Git/.fgit/caches/";
    for(int i = 0; i<FgitPaths.size(); i++){
        if(FgitPaths[i].compare(filePath)== 0){
            CachePath = fgitCachePath + FgitPaths[i];
            isExist = true;
            cout << "FILE EXIST";
            break;
        }
    }
    if(isExist){
        string FgitContent = readFileIntoString(CachePath);
        string currentContent = readFileIntoString(filePath);
        cout << endl << "FGIT " << FgitContent;
        cout << endl << "REPO " << currentContent << endl;
        if(Diff::isDiff(currentContent,FgitContent)){
            cout << endl << "MODIFIED";
            return true;
        }
        else{
            cout << "UNMODIFIED";
            return false;
        }
        return Diff::isDiff(FgitContent,currentContent);
    }
    else{
        cout << "FILE DO NOT EXIST";
    }
    
    return true;
}

string Staged::readFileIntoString(const string& path) {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
            << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}
