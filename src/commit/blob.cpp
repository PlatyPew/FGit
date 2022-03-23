#include "blob.hpp"

#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = filesystem;

Blob::Blob(string id, string path) : id(id), path(path) {}

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

void Blob::setPerms(fs::perms perms) {
    this->perms = perms;
}

void Blob::setDiff(string diff) {
    this->diff = diff;
}
