#pragma once

#include "blob.hpp"

#include <stack>
#include <string>

class Reset {
  private:
    std::string path;
    std::string contents = "";

    void patchContents(std::stack<Blob> blobs);

  public:
    Reset(std::string path, std::stack<Blob> blobs);

    std::string getPath();
    std::string getContents();

    static void reset(std::string id);
};
