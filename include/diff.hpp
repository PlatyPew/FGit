#pragma once

#include <iostream>

using namespace std;

class Diff {
  public:
    static string diff(string text1, string text2);
    static string patch(string patch, string text);
};
