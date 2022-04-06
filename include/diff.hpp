#pragma once

#include "defaults.hpp"

#include "diff_match_patch.h"
#include "sha1.hpp"

#include <fstream>
#include <string>

class Diff {
  private:
    std::string path;
    std::string contents = "";
    void print();

  public:
    Diff(std::string path, bool deleted, bool binary);
    static void diff();

    /**
     * @brief creates a unidiff patch between text1 -> text 2
     *
     * @param prev: old text
     * @param curr: new text
     *
     * @return unidiff patch
     */
    static std::string diff(std::string prev, std::string curr) {
        diff_match_patch<std::string> dmp;
        return dmp.patch_toText(dmp.patch_make(prev, curr));
    }

    /**
     * @brief applies patch -> text to get new text
     *
     * @param patch: unidiff patch
     * @param prev: text to patch
     *
     * @return patched string
     */
    static std::string patch(std::string patch, std::string prev) {
        diff_match_patch<std::string> dmp;
        return dmp.patch_apply(dmp.patch_fromText(patch), prev).first;
    }

    /**
     * @brief checks if there is a difference between strings
     *
     * @param prev: previous string
     * @param curr: current string
     * @return true if there is a difference
     */
    static bool isDiff(std::string prev, std::string curr) {
        SHA1 checksum1, checksum2;
        checksum1.update(prev);
        checksum2.update(curr);
        return checksum1.final() != checksum2.final();
    }
};
