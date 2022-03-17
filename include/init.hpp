#pragma once

#include <iostream>

using std::string;

class Init {
  private:
    const static string directory;
    const static string objects;
    const static string refs;
    const static string heads;

    static bool exists();
    static bool createTree();

  public:
    static bool init();
    static bool init(string);
};
