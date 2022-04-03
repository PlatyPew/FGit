#pragma once

#include "cereal/access.hpp"

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class Blob {
    friend class cereal::access;

  private:
    virtual std::string createDiff(bool genesis);

    template <class Archive> void serialize(Archive& archive) {
        archive(path, perms, diff, deletion, binary);
    }

  protected:
    std::string path;
    fs::perms perms;
    std::string diff;
    bool deletion;
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
};
