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

string Commit::createId() {
    // Serialise data
    stringstream ss;
    toSerial(ss, *this);

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

Commit Commit::commit(map<string, bool> files, string author, string message) {
    map<string, Blob> blobs;
    for (auto const& [f, del] : files) {
        Blob b(f, del);
        blobs.insert(pair<string, Blob>(f, b));
    }

    Commit c(blobs, author, message);
    c.createCommit();

    return c;
}

string Commit::getHeadCommit() {
    if (Commit::isGenesis())
        return "";

    ifstream in(Defaults::fgitHead);
    stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

void Commit::readCommit() {
    if (Commit::isGenesis())
        return;

    ifstream in;
    in.open(Defaults::fgitObjects + Commit::getHeadCommit());
    in >> *this;
    in.close();
}

void Commit::readCommit(string id) {
    ifstream in;
    in.open(Defaults::fgitObjects + id);
    in >> *this;
    in.close();
}

void Commit::writeCommit() {
    // If it is root commit
    ofstream out;
    out.open(Defaults::fgitObjects + this->getId());
    out << *this;
    out.close();

    out.open(Defaults::fgitHead);
    out << this->getId();
    out.close();

    for (auto const& [path, blob] : this->getBlobs()) {
        if (((Blob)blob).getDeletion())
            fs::remove(Defaults::fgitCaches + path);
        else
            fs::copy(path, Defaults::fgitCaches + path, fs::copy_options::update_existing);
    }
}

void Commit::createCommit() {
    this->prevId = Commit::getHeadCommit();
    this->id = this->createId();
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
