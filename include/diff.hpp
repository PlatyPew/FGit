#pragma once

#include "diff_match_patch.h"

#include <iostream>

using namespace std;

class Diff {
  public:
    static string diff(string prev, string curr) {
        diff_match_patch<string> dmp;
        return dmp.patch_toText(dmp.patch_make(prev, curr));
    }

    static string patch(string patch, string prev) {
        diff_match_patch<string> dmp;
        return dmp.patch_apply(dmp.patch_fromText(patch), prev).first;
    }
    static bool isDiff(string prev, string curr) {
        return Diff::diff(prev, curr) == "";
    }
};
