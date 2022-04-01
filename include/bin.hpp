#pragma once

#include "blob.hpp"

#include "cereal/access.hpp"
#include "cereal/types/base_class.hpp"

class Bin : public Blob {
    friend class cereal::access;

  private:
    std::string createDiff(bool genesis);

    template <class Archive> void serialize(Archive& archive) {
        archive(cereal::base_class<Blob>(this));
    }

  public:
    Bin(){};
    Bin(std::string path, bool deletion = false);

    std::string getContents();

    friend std::ostream& operator<<(std::ostream& out, const Blob& blob);
    friend std::istream& operator>>(std::istream& in, Blob& blob);
};
