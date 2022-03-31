#pragma once

#include "commit.hpp"

using namespace std;

class Log {
  private:
    static void print(Commit commit);

  public:
    static void log();
    static void log(string id);
};
