#include "commit.hpp"

#include "blob.hpp"
#include "defaults.hpp"

#include "cereal/archives/binary.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/string.hpp"
#include "sha1.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;
namespace fs = filesystem;

Commit::Commit(map<string, Blob> blobs, string author, string message) {
    this->blobs = blobs;
    this->author = author;
    this->message = message;
}

string createId(Commit commit) {
    // Serialise data
    stringstream ss;
    toSerial(ss, commit);

    // Hash serial
    SHA1 checksum;
    checksum.update(ss.str());
    return checksum.final();
}

string Commit::getId() {
    return this->id;
}

map<string, Blob> Commit::getBlobs() {
    return this->blobs;
}

string Commit::getPrevId() {
    return this->prevId;
}

string Commit::getAuthor() {
    return this->author;
}

string Commit::getMessage() {
    return this->message;
}

bool Commit::isGenesis() {
    return fs::is_empty(Defaults::fgitObjects);
};

Commit Commit::commit(vector<string> files, string author, string message) {
    map<string, Blob> blobs;
    for (string f : files) {
        Blob b(f);
        blobs.insert(pair<string, Blob>(f, b));
    }

    Commit c(blobs, author, message);
    createCommit(c);

    return c;
}

void Commit::writeCommit() {
    cout << this;
}

void createCommit(Commit& commit) {
    commit.id = createId(commit);
}

void toSerial(stringstream& serial, Commit commit) {
    cereal::BinaryOutputArchive oarchive(serial);
    oarchive(commit);
}

void fromSerial(stringstream& serial, Commit& commit) {
    cereal::BinaryInputArchive iarchive(serial);
    iarchive(commit);
}

ostream& operator<<(ostream& out, const Commit& commit) {
    stringstream ss;
    toSerial(ss, commit);
    out << ss.str();
    return out;
}

istream& operator>>(istream& in, Commit& commit) {
    stringstream ss;
    ss << in.rdbuf();
    fromSerial(ss, commit);
    return in;
}
