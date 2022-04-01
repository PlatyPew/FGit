#pragma once

#include "commit.hpp"

class Log {
  private:
    static void print(Commit commit);

  public:
    static void log();
    static void log(std::string id);
};
