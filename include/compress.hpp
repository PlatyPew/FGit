#pragma once

#include "gzip/compress.hpp"
#include "gzip/decompress.hpp"

class Compress {
  public:
    static std::string compress(std::string uncompressedData) {
        const char* ptr = uncompressedData.data();
        std::size_t size = uncompressedData.size();
        return gzip::compress(ptr, size);
    }

    static std::string decompress(std::string compressedData) {
        const char* ptr = compressedData.data();
        std::size_t size = compressedData.size();
        return gzip::decompress(ptr, size);
    }
};
