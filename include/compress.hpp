#pragma once

#include "gzip/compress.hpp"
#include "gzip/decompress.hpp"

class Compress {
  public:
    /**
     * @brief compresses string using gzip
     *
     * @param uncompressedData: string to compress
     *
     * @return compressed string
     */
    static std::string compress(std::string uncompressedData) {
        const char* ptr = uncompressedData.data();
        std::size_t size = uncompressedData.size();
        return gzip::compress(ptr, size);
    }

    /**
     * @brief decompreses string using gzip
     *
     * @param compressedData: string to decompress
     *
     * @return decompressed string
     */
    static std::string decompress(std::string compressedData) {
        const char* ptr = compressedData.data();
        std::size_t size = compressedData.size();
        return gzip::decompress(ptr, size);
    }
};
