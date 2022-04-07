#pragma once

#include "cereal/access.hpp"

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class Blob {
    friend class cereal::access;

  private:
    std::string path;
    bool deletion;
    fs::perms perms;
    std::string diff;

    template <class Archive> void serialize(Archive& archive) {
        archive(path, perms, diff, deletion, binary);
    }

  protected:
    bool binary = false;

  public:
    Blob(){};
    Blob(std::string path, bool deletion = false);

    std::string getPath();
    fs::perms getPerms();
    std::string getDiff();
    bool getDeletion();
    bool getBinary();
    std::string getContents(std::string prevContents);
    void setDiff(std::string diff);
    virtual std::string createDiff(bool genesis);
};
