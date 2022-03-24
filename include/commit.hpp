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
    string id;
    vector<Blob> blobs;
    string prevId;

    friend string createId(Commit commit);
    friend void toSerial(stringstream& serial, Commit commit);
    friend void fromSerial(stringstream serial, Commit& commit);

  public:
    Commit(vector<Blob> blobs, string author, string message);

    string getAuthor();
    string getMessage();
    string getId();
    vector<Blob> getBlobs();
    string getPrevId();

    static bool isGenesis();

    friend void createCommit(Commit& commit);
    friend ostream& operator<<(ostream& out, const Commit& commit);

    template <class Archive> void save(Archive& archive) const {
        archive(author, message, id, blobs, prevId);
    }

    template <class Archive> void load(Archive& archive) {
        archive(author, message, id, blobs, prevId);
    }
};
