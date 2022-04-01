#include "diff.hpp"

#include "diff_match_patch.h"

#include <iostream>

using namespace std;

string Diff::diff(string prev, string curr) {
    diff_match_patch<string> dmp;
    return dmp.patch_toText(dmp.patch_make(prev, curr));
}

string Diff::patch(string patch, string prev) {
    diff_match_patch<string> dmp;
    return dmp.patch_apply(dmp.patch_fromText(patch), prev).first;
}

bool Diff::isDiff(string prev, string curr) {
    return Diff::diff(prev, curr) == "";
}
