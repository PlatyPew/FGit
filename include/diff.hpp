#pragma once

#include <iostream>

using namespace std;

class Diff {
  public:
    static string diff(string prev, string curr);
    static string patch(string patch, string text);
    static bool isDiff(string prev, string curr);
    static string unpatch(string patch, string curr);
};
