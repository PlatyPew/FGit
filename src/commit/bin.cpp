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

Bin::Bin(string path, bool deletion) : Blob(path, deletion) {
    this->binary = true;
}

/**
 * @brief stores the binary file
 *
 * @param genesis: if there are any commits prior
 * @return binary file
 */
string Bin::createDiff(bool genesis) {
    if (!fs::exists(this->getPath()))
        throw "File does not exist";

    if (this->getDeletion())
        return "";

    // Read file and convert to string
    ifstream fileNew(this->getPath(), std::ios::binary);
    stringstream newData;
    if (!fileNew)
        throw "File cannot be opened";

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
