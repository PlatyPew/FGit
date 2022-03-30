#pragma once

#include <iostream>

using std::string;

class Init {
  private:
    static bool createTree();

  public:
    static bool exists();
    static bool init();
    static string getHeadId();
};
