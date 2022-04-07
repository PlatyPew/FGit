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

using std::ifstream, std::istream, std::ostream, std::string, std::stringstream;
namespace fs = std::filesystem;

Blob::Blob(string path, bool deletion) {
    this->path = path;
    this->perms = fs::status(path).permissions();
    this->deletion = deletion;
}

/**
 * @brief creates the diff between the previous state and current state
 *
 * @param genesis: if the commit is the first commit
 * @return unidiff patch format
 */
string Blob::createDiff(bool genesis) {
    if (this->deletion)
        return "";

    if (!fs::exists(this->path))
        throw "File does not exist";

    // Read file and convert to string
    ifstream fileNew(this->path);
    stringstream newData;
    if (!fileNew)
        throw "File cannot be opened";

    newData << fileNew.rdbuf();
    fileNew.close();

    if (genesis)
        return Diff::diff("", newData.str());

    // Read old file
    ifstream fileOld(Defaults::fgitCaches + this->path);
    stringstream oldData;
    if (!fileOld)
        throw "File cannot be opened";

    oldData << fileOld.rdbuf();
    fileOld.close();

    return Diff::diff(oldData.str(), newData.str());
}

/**
 * @brief getter for the path of the file
 *
 * @return path of the file
 */
string Blob::getPath() {
    return this->path;
}

/**
 * @brief getter for the permissions of the file
 *
 * @return permissions of the file
 */
fs::perms Blob::getPerms() {
    return this->perms;
}

/**
 * @brief getter for the unidiff patch
 *
 * @return unidiff patch
 */
string Blob::getDiff() {
    return this->diff;
}

/**
 * @brief getter if the file is to be deleted
 *
 * @return true if file is deleted
 */
bool Blob::getDeletion() {
    return this->deletion;
}

/**
 * @brief getter if file is binary type
 *
 * @return true if binary
 */
bool Blob::getBinary() {
    return this->binary;
}

/**
 * @brief applies the patch
 *
 * @param prevContents: contents of the previous file
 * @return patched contents
 */
string Blob::getContents(string prevContents) {
    return Diff::patch(this->diff, prevContents);
}

void Blob::setDiff(string diff) {
    this->diff = diff;
}
