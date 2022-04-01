#include "bin.hpp"
#include "commit.hpp"
#include "defaults.hpp"
#include "diff.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using std::ifstream, std::istream, std::ostream, std::string, std::stringstream;
namespace fs = std::filesystem;

Bin::Bin(string path, bool deletion) {
    this->path = path;
    this->perms = fs::status(path).permissions();
    this->deletion = deletion;
    this->diff = createDiff(Commit::isGenesis());
}

/**
 * @brief stores the binary file
 *
 * @param genesis: if there are any commits prior
 * @return binary file
 */
string Bin::createDiff(bool genesis) {
    if (!fs::exists(this->path))
        return "";

    if (this->deletion)
        return "";

    // Read file and convert to string
    ifstream fileNew(this->path, std::ios::binary);
    stringstream newData;
    if (!fileNew)
        return "";

    newData << fileNew.rdbuf();
    fileNew.close();

    return newData.str();
}

/**
 * @brief get contents of the binary
 *
 * @return contenst of binary file
 */
string Bin::getContents() {
    return this->getDiff();
}
