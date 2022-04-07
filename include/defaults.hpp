#pragma once

#include <string>
#include <vector>

namespace Defaults {
const std::string fgitDirectory = ".fgit/";
const std::string fgitObjects = fgitDirectory + "objects/";
const std::string fgitRefs = fgitDirectory + "refs/";
const std::string fgitCaches = fgitDirectory + "caches/";
const std::string fgitHead = fgitRefs + "HEAD";
const std::string fgitLatest = fgitRefs + "LATEST";
const std::string home = ".";
const std::vector<std::string> gitIgnore = {".gitignore",".gitmodules","CMakeLists.txt","LICENSE","README.md", "password.txt"} ;     
}; // namespace Defaults
