#pragma once

#include "blob.hpp"

#include <iostream>
#include <vector>

using namespace std;

class Commit {
  private:
    string commitHash;
    vector<Blob> blobs;
    string prevHash;
    string author;
    string message;

  public:
    Commit(vector<Blob> blobs, string author, string message);

    void setCommitHash(string commitHash);
    void setBlobs(vector<Blob> blobs);
    void setPrevHash(string prevHash);
    void setAuthor(string author);
    void setMessage(string message);

    string getCommitHash();
    vector<Blob> getBlobs();
    string getPrevHash();
    string getAuthor();
    string getMessage();
};
