#include "diff.hpp"

#include "diff_match_patch.h"

#include <iostream>

using namespace std;

string Diff::diff(string curr, string prev) {
    diff_match_patch<string> dmp;
    return dmp.patch_toText(dmp.patch_make(prev, curr));
}

string Diff::patch(string patch, string curr) {
    diff_match_patch<string> dmp;
    return dmp.patch_apply(dmp.patch_fromText(patch), curr).first;
}
