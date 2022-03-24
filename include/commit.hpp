#pragma once

#include "blob.hpp"

#include "cereal/access.hpp"

#include <iostream>
#include <vector>

using namespace std;

class Commit {
    friend class cereal::access;

  private:
    string author;
    string message;
    string commitHash;
    vector<Blob> blobs;
    string prevHash;

  public:
    Commit(vector<Blob> blobs, string author, string message);

    string getCommitHash();
    vector<Blob> getBlobs();
    string getPrevHash();
    string getAuthor();
    string getMessage();

    void setCommitHash(string commitHash);
    void setBlobs(vector<Blob> blobs);
    void setPrevHash(string prevHash);
    void setAuthor(string author);
    void setMessage(string message);

    static bool isGenesis();

    friend stringstream createSerial(Commit commit);
    friend void writeObject(Commit& commit);

    template <class Archive> void save(Archive& archive) const {
        archive(author, message, commitHash, blobs, prevHash);
    }

    template <class Archive> void load(Archive& archive) {
        archive(author, message, commitHash, blobs, prevHash);
    }
};
