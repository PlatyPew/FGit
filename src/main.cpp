#include "diff.hpp"
#include "init.hpp"
#include "log.hpp"

#include "add.hpp"
#include "bin.hpp"
#include "blob.hpp"
#include "commit.hpp"
#include "compress.hpp"
#include "reset.hpp"
#include "status.hpp"

#include <iostream>
#include <vector>

using namespace std;

void runSubCmd(string subCmd, int argc, char** argv) {
    if (subCmd == "init")
        Init::init();

    // Check if .fgit exists
    if (!Init::exists())
        throw "FGit Repository has not been initialised";

    if (subCmd == "log")
        Log::log();
    else if (subCmd == "reset") {
        if (argc == 3)
            Reset::reset(argv[2]);
        else
            throw "Missing commit id";
    }

    if (subCmd == "add") {
        Add add;
        if (argc == 2) {
            add.add();
        } else {
            add.add(argv[2]);
        }
    }
}

int main(int argc, char** argv) {
    if (argc >= 2) {
        string subcmd(argv[1]);
        runSubCmd(subcmd, argc, argv);
    }

    return 0;
}
