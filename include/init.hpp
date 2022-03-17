#pragma once

#include <iostream>

using std::string;

class Init {
  private:
    const static string directory;
    static bool exists();

  public:
    static bool init();
    static bool init(string);
};
