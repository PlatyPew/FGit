#pragma once

#include "blob.hpp"

#include "cereal/access.hpp"

#include <iostream>
#include <map>

using namespace std;

class Commit {
    friend class cereal::access;

  private:
    string author;
    string message;
    string id;
    map<string, Blob> blobs;
    string prevId;

    friend string createId(Commit commit);
    friend void toSerial(stringstream& serial, Commit commit);
    friend void fromSerial(stringstream& serial, Commit& commit);

  public:
    Commit(){};
    Commit(map<string, Blob> blobs, string author, string message);

    string getAuthor();
    string getMessage();
    string getId();
    map<string, Blob> getBlobs();
    string getPrevId();

    static bool isGenesis();
    static string getHeadCommit();
    static Commit commit(map<string, bool> files, string author, string message);

    void readCommit();
    void readCommit(string id);
    void writeCommit();

    friend void createCommit(Commit& commit);
    friend ostream& operator<<(ostream& out, const Commit& commit);
    friend istream& operator>>(istream& in, Commit& commit);

    template <class Archive> void save(Archive& archive) const {
        archive(author, message, id, blobs, prevId);
    }

    template <class Archive> void load(Archive& archive) {
        archive(author, message, id, blobs, prevId);
    }
};
