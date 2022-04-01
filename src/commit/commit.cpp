#include "commit.hpp"
#include "bin.hpp"
#include "blob.hpp"
#include "compress.hpp"
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

using std::ifstream, std::istream, std::map, std::ofstream, std::ostream, std::pair, std::string,
    std::stringstream;
namespace fs = std::filesystem;

Commit::Commit(map<string, Blob> blobs, string author, string message) {
    this->blobs = blobs;
    this->author = author;
    this->message = message;
}

/**
 * @brief creates an id of the commit using a sha1 hash
 *
 * @return sha1 has of the object
 */
string Commit::createId() {
    // Serialise data
    stringstream ss;
    toSerial(ss, *this);

    // Hash serial
    SHA1 checksum;
    checksum.update(ss.str());
    return checksum.final();
}

/**
 * @brief getter for commit id
 *
 * @return sha1 hash of commit
 */
string Commit::getId() {
    return this->id;
}

/**
 * @brief getter for blobs
 *
 * @return map of the path its respective blob
 */
map<string, Blob> Commit::getBlobs() {
    return this->blobs;
}

/**
 * @brief getter for parent commit id
 *
 * @return sha1 hash of parent commit
 */
string Commit::getPrevId() {
    return this->prevId;
}

/**
 * @brief getter for commit author
 *
 * @return author of the commit
 */
string Commit::getAuthor() {
    return this->author;
}

/**
 * @brief getter for commit message
 *
 * @return message of the commit
 */
string Commit::getMessage() {
    return this->message;
}

/**
 * @brief checks if there are any commits before in the tree
 *
 * @return true if no previous commits exist
 */
bool Commit::isGenesis() {
    return fs::is_empty(Defaults::fgitObjects);
};

/**
 * @brief wrapper function to create commit object
 *
 * @param files: a map that contains the path, and a pair which contains if deleted and binary file
 * @param author: author of the commit
 * @param message: message of the commit
 * @return a commit object
 */
Commit Commit::commit(map<string, pair<bool, bool>> files, string author, string message) {
    map<string, Blob> blobs;
    for (auto const& [f, attr] : files) {
        // If it is a binary file
        if (attr.second) {
            Bin b(f, attr.first);
            blobs.insert(pair<string, Blob>(f, (Blob)b));
        } else {
            Blob b(f, attr.first);
            blobs.insert(pair<string, Blob>(f, b));
        }
    }

    Commit c(blobs, author, message);
    c.createCommit();

    return c;
}

/**
 * @brief gets the commit id of where the HEAD is
 *
 * @return commit id of HEAD
 */
string Commit::getHeadCommit() {
    if (Commit::isGenesis())
        return "";

    ifstream in(Defaults::fgitHead);
    stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

/**
 * @brief reads the commit at the HEAD
 *
 */
void Commit::readCommit() {
    if (Commit::isGenesis())
        return;

    this->readCommit(Commit::getHeadCommit());
}

/**
 * @brief reads the commit based on commit id
 *
 * @param id: sha1 hash of the commit
 */
void Commit::readCommit(string id) {
    ifstream in;
    in.open(Defaults::fgitObjects + id);
    in >> *this;
    in.close();
}

/**
 * @brief writes the commit into .fgit directory
 *
 */
void Commit::writeCommit() {
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

/**
 * @brief updates the commit id and the parent commit id
 *
 */
void Commit::createCommit() {
    this->prevId = Commit::getHeadCommit();
    this->id = this->createId();
}

/**
 * @brief converts Commit object to serial
 *
 * @param commit: Commit to read from
 */
void toSerial(stringstream& serial, Commit commit) {
    cereal::BinaryOutputArchive oarchive(serial);
    oarchive(commit);
}

/**
 * @brief converts serial to Commit object
 *
 * @param commit Commit to write to
 */
void fromSerial(stringstream& serial, Commit& commit) {
    cereal::BinaryInputArchive iarchive(serial);
    iarchive(commit);
}

ostream& operator<<(ostream& out, const Commit& commit) {
    stringstream ss;
    toSerial(ss, commit);
    out << Compress::compress(ss.str());
    return out;
}

istream& operator>>(istream& in, Commit& commit) {
    stringstream ss;
    ss << in.rdbuf();
    stringstream sss;
    sss << Compress::decompress(ss.str());
    fromSerial(sss, commit);
    return in;
}
