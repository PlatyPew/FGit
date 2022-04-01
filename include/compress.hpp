#pragma once

#include <iostream>

using namespace std;

class Compress {
  public:
    static std::string compress(std::string uncompressedData);

    static std::string decompress(std::string compressedData);
};
