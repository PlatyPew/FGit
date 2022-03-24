#include "blob.hpp"
#include "commit.hpp"
#include "diff.hpp"

#include "cereal/archives/binary.hpp"
#include "cereal/types/string.hpp"
#include "sha1.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
namespace fs = filesystem;

Blob::Blob() {}

Blob::Blob(string path) {
    this->path = path;
    this->perms = fs::status(path).permissions();

    if (Commit::isGenesis())
        this->diff = createDiff();
}

/**
 * @brief Creates diff if its te genesis commit
 *
 */
string Blob::createDiff() {
    if (!fs::exists(this->path))
        return NULL;

    // Read file and convert to string
    ifstream file(this->path);
    ostringstream ss;
    if (!file)
        return NULL;

    ss << file.rdbuf();

    return Diff::diff("", ss.str());
}

string createId(Blob blob) {
    // Serialise data
    stringstream ss;
    toSerial(ss, blob);

    // Hash serial
    SHA1 checksum;
    checksum.update(ss.str());
    return checksum.final();
}

string Blob::getId() {
    return this->id;
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

void createBlob(Blob& blob) {
    blob.id = createId(blob);
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
