#include "compress.hpp"

#include "gzip/compress.hpp"
#include "gzip/decompress.hpp"

#include <string>

std::string Compress::compress(std::string uncompressedData) {
    const char* ptr = uncompressedData.data();
    std::size_t size = uncompressedData.size();
    return gzip::compress(ptr, size);
}

std::string Compress::decompress(std::string compressedData) {
    const char* ptr = compressedData.data();
    std::size_t size = compressedData.size();
    return gzip::decompress(ptr, size);
}
