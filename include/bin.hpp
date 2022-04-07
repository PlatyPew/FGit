#pragma once

#include "blob.hpp"

#include "cereal/access.hpp"
#include "cereal/types/base_class.hpp"

class Bin : public Blob {
    friend class cereal::access;

  private:
    template <class Archive> void serialize(Archive& archive) {
        archive(cereal::base_class<Blob>(this));
    }

  public:
    Bin(){};
    Bin(std::string path, bool deletion = false);

    std::string getContents();
    std::string createDiff(bool genesis) override;
};
