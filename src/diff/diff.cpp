#include "diff.hpp"

#include "diff_match_patch.h"

#include <iostream>

using namespace std;

string Diff::diff(string text1, string text2) {
    diff_match_patch<string> dmp;
    return dmp.patch_toText(dmp.patch_make(text1, text2));
}

string Diff::patch(string patch, string text) {
    diff_match_patch<string> dmp;
    return dmp.patch_apply(dmp.patch_fromText(patch), text).first;
}
