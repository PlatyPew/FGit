#pragma once

#include "blob.hpp"

#include "cereal/access.hpp"

#include <map>
#include <string>

class Commit {
    friend class cereal::access;

  private:
    std::string author;
    std::string message;
    std::string id;
    std::map<std::string, Blob> blobs;
    std::string prevId = "";
    std::string timestamp;

    void createCommit();
    std::string createId();

    friend void toSerial(std::stringstream& serial, Commit commit);
    friend void fromSerial(std::stringstream& serial, Commit& commit);

  public:
    Commit(){};
    Commit(std::map<std::string, Blob> blobs, std::string author, std::string message);

    std::string getAuthor();
    std::string getMessage();
    std::string getId();
    std::map<std::string, Blob> getBlobs();
    std::string getPrevId();
    std::string getTimestamp();

    static bool isGenesis();
    static std::string getHeadCommit();
    static Commit commit(std::map<std::string, std::pair<bool, bool>> files, std::string author,
                         std::string message);

    void readCommit();
    void readCommit(std::string id);
    void writeCommit();

    friend std::ostream& operator<<(std::ostream& out, const Commit& commit);
    friend std::istream& operator>>(std::istream& in, Commit& commit);

    template <class Archive> void save(Archive& archive) const {
        archive(author, message, id, blobs, prevId, timestamp);
    }

    template <class Archive> void load(Archive& archive) {
        archive(author, message, id, blobs, prevId, timestamp);
    }
};
