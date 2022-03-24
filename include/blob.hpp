#pragma once

#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = filesystem;

class Blob {
  private:
    string path;
    string id;
    fs::perms perms;
    string diff;

    string createDiff();
    string createDiff(string head);

    friend string createId(Blob blob);

    template <class Archive> void serialize(Archive& archive) {
        archive(path, perms, diff);
    }

  public:
    Blob(string path);

    string getId();
    string getPath();
    fs::perms getPerms();
    string getDiff();

    friend void createBlob(Blob& blob);
    friend stringstream createSerial(Blob blob);
    friend ostream& operator<<(ostream& out, const Blob& blob);
};
