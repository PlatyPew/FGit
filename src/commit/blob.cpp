#include "blob.hpp"
#include "commit.hpp"
#include "defaults.hpp"
#include "diff.hpp"
#include "init.hpp"

#include "cereal/archives/binary.hpp"
#include "cereal/types/string.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
namespace fs = filesystem;

Blob::Blob(string path, bool deletion) {
    this->path = path;
    this->perms = fs::status(path).permissions();
    this->deletion = deletion;
    this->diff = createDiff(Commit::isGenesis());
}

string Blob::createDiff(bool genesis) {
    if (!fs::exists(this->path))
        return "";

    if (this->deletion)
        return "";

    // Read file and convert to string
    ifstream fileNew(this->path);
    stringstream newData;
    if (!fileNew)
        return "";

    newData << fileNew.rdbuf();
    fileNew.close();

    if (genesis)
        return Diff::diff("", newData.str());

    // Read old file
    ifstream fileOld(Defaults::fgitHead + this->path);
    stringstream oldData;
    oldData << fileOld.rdbuf();
    fileOld.close();

    return Diff::diff(oldData.str(), newData.str());
}

string Blob::getPath() {
    return this->path;
}

fs::perms Blob::getPerms() {
    return this->perms;
}

string Blob::getDiff() {
    return this->diff;
}

bool Blob::getDeletion() {
    return this->deletion;
}

void toSerial(stringstream& serial, Blob blob) {
    cereal::BinaryOutputArchive oarchive(serial);
    oarchive(blob);
}

void fromSerial(stringstream& serial, Blob& blob) {
    cereal::BinaryInputArchive iarchive(serial);
    iarchive(blob);
}

ostream& operator<<(ostream& out, const Blob& blob) {
    stringstream ss;
    toSerial(ss, blob);
    out << ss.str();
    return out;
}

istream& operator>>(istream& in, Blob& blob) {
    stringstream ss;
    ss << in.rdbuf();
    fromSerial(ss, blob);
    return in;
}
