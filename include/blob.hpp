#pragma once

#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = filesystem;

class Blob {
  private:
    const string id;
    const string path;
    fs::perms perms;
    string diff;

public:
    Blob(string id, string path);

    string getId();
    string getPath();
    fs::perms getPerms();
    string getDiff();

    void setPerms(fs::perms perms);
    void setDiff(string diff);
};
