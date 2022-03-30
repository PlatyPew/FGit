#pragma once

#include <iostream>

using namespace std;

namespace Defaults {
const string fgitDirectory = ".fgit/";
const string fgitObjects = fgitDirectory + "objects/";
const string fgitRefs = fgitDirectory + "refs/";
const string fgitCaches = fgitDirectory + "caches/";
const string fgitHead = fgitRefs + "HEAD";
}; // namespace Defaults
