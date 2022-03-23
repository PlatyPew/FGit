#include "blob.hpp"
#include "diff.hpp"

#include "sha1.hpp"

#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = filesystem;

Blob::Blob(string path) : path(path) {}

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

void Blob::setId(string id) {
    this->id = id;
}

void Blob::setPerms(fs::perms perms) {
    this->perms = perms;
}

void Blob::setDiff(string diff) {
    this->diff = diff;
}

void Blob::createBlob() {
}
