#pragma once

#include "diff_match_patch.h"

#include <string>

class Diff {
  public:
    static std::string diff(std::string prev, std::string curr) {
        diff_match_patch<std::string> dmp;
        return dmp.patch_toText(dmp.patch_make(prev, curr));
    }

    static std::string patch(std::string patch, std::string prev) {
        diff_match_patch<std::string> dmp;
        return dmp.patch_apply(dmp.patch_fromText(patch), prev).first;
    }
    static bool isDiff(std::string prev, std::string curr) {
        return Diff::diff(prev, curr) == "";
    }
};
