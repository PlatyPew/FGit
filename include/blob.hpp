#pragma once

#include "cereal/access.hpp"

#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = filesystem;

class Blob {
    friend class cereal::access;

  private:
    string path;
    string id;
    fs::perms perms;
    string diff;

    string createDiff();
    string createDiff(string head);

    friend string createId(Blob blob);
    friend void toSerial(stringstream& serial, Blob blob);
    friend void fromSerial(stringstream& serial, Blob& blob);

    template <class Archive> void serialize(Archive& archive) {
        archive(path, perms, diff);
    }

  public:
    Blob(){};
    Blob(string path);

    string getId();
    string getPath();
    fs::perms getPerms();
    string getDiff();

    friend void createBlob(Blob& blob);
    friend ostream& operator<<(ostream& out, const Blob& blob);
    friend istream& operator>>(istream& in, Blob& blob);
};
