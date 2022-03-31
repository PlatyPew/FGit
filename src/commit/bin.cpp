#include "bin.hpp"
#include "commit.hpp"
#include "defaults.hpp"
#include "diff.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
namespace fs = filesystem;

Bin::Bin(string path, bool deletion) {
    this->path = path;
    this->perms = fs::status(path).permissions();
    this->deletion = deletion;
    this->diff = createDiff(Commit::isGenesis());
}

string Bin::createDiff(bool genesis) {
    if (!fs::exists(this->path))
        return "";

    if (this->deletion)
        return "";

    // Read file and convert to string
    ifstream fileNew(this->path, ios::binary);
    stringstream newData;
    if (!fileNew)
        return "";

    newData << fileNew.rdbuf();
    fileNew.close();

    return Diff::diff("", newData.str());
}

ostream& operator<<(ostream& out, const Bin& blob) {
    stringstream ss;
    toSerial(ss, blob);
    out << ss.str();
    return out;
}

istream& operator>>(istream& in, Bin& blob) {
    stringstream ss;
    ss << in.rdbuf();
    fromSerial(ss, blob);
    return in;
}
