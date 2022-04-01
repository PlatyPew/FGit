#pragma once

#include "cereal/access.hpp"

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class Blob {
    friend class cereal::access;

  private:
    std::string createDiff(bool genesis);

    friend void toSerial(std::stringstream& serial, Blob blob);
    friend void fromSerial(std::stringstream& serial, Blob& blob);

    template <class Archive> void serialize(Archive& archive) {
        archive(path, perms, diff, deletion);
    }

  protected:
    std::string path;
    fs::perms perms;
    std::string diff;
    bool deletion;

  public:
    Blob(){};
    Blob(std::string path, bool deletion = false);

    std::string getPath();
    fs::perms getPerms();
    std::string getDiff();
    bool getDeletion();
    std::string getContents(std::string prevContents);

    friend std::ostream& operator<<(std::ostream& out, const Blob& blob);
    friend std::istream& operator>>(std::istream& in, Blob& blob);
};
