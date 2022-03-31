#include "diff.hpp"
#include "init.hpp"
#include "log.hpp"

#include "bin.hpp"
#include "blob.hpp"
#include "commit.hpp"
#include "log.hpp"

#include <iostream>
#include <vector>

using namespace std;

void runSubCmd(string subCmd) {
    if (subCmd == "init") {
        Init::init();
        return;
    }

    // Check if .fgit exists
    if (!Init::exists()) {
        cout << "FGit Repository has not been initialised! Aborting..." << endl;
        return;
    }

    if (subCmd == "log")
        Log::log();
}

int main(int argc, char** argv) {
    if (argc >= 2) {
        string subcmd(argv[1]);
        runSubCmd(subcmd);
    }

    return 0;
}
