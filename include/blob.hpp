#pragma once

#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = filesystem;

class Blob {
  private:
    const string path;
    string id;
    fs::perms perms;
    string diff;

public:
    Blob(string path);

    string getId();
    string getPath();
    fs::perms getPerms();
    string getDiff();

    void setId(string id);
    void setPerms(fs::perms perms);
    void setDiff(string diff);

    void createBlob();
};
