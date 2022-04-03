#pragma once

#include <string>

namespace Defaults {
const std::string fgitDirectory = ".fgit/";
const std::string fgitObjects = fgitDirectory + "objects/";
const std::string fgitRefs = fgitDirectory + "refs/";
const std::string fgitCaches = fgitDirectory + "caches/";
const std::string fgitHead = fgitRefs + "HEAD";
const std::string fgitLatest = fgitRefs + "LATEST";
}; // namespace Defaults
