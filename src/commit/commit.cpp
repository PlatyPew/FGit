#include "commit.hpp"

#include "blob.hpp"

#include <iostream>
#include <vector>

Commit::Commit(vector<Blob> blobs, string author, string message) {
    this->blobs = blobs;
    this->author = author;
    this->message = message;
}

string Commit::getCommitHash() {
    return this->commitHash;
}

vector<Blob> Commit::getBlobs() {
    return this->blobs;
}

string Commit::getPrevHash() {
    return this->prevHash;
}

string Commit::getAuthor() {
    return this->author;
}

string Commit::getMessage() {
    return this->message;
}

void Commit::setCommitHash(string commitHash) {
    this->commitHash = commitHash;
}

void Commit::setBlobs(vector<Blob> blobs) {
    this->blobs = blobs;
}

void Commit::setPrevHash(string prevHash) {
    this->prevHash = prevHash;
}

void Commit::setAuthor(string author) {
    this->author = author;
}

void Commit::setMessage(string message) {
    this->message = message;
}
