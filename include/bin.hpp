#pragma once

#include "blob.hpp"
#include "cereal/access.hpp"
#include "cereal/types/base_class.hpp"

class Bin : public Blob {
    friend class cereal::access;

  private:
    string createDiff(bool genesis);

    template <class Archive> void serialize(Archive& archive) {
        archive(cereal::base_class<Blob>(this));
    }

  public:
    Bin(){};
    Bin(string path, bool deletion = false);

    friend ostream& operator<<(ostream& out, const Blob& blob);
    friend istream& operator>>(istream& in, Blob& blob);
};
