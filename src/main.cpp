#include "diff.hpp"
#include "init.hpp"
#include "log.hpp"

#include "bin.hpp"
#include "blob.hpp"
#include "commit.hpp"
#include "add.hpp"

#include <iostream>
#include <vector>

using namespace std;

void runSubCmd(string subCmd,int argc ,char ** argv) {
    if (subCmd == "init")
        Init::init();

    // Check if .fgit exists
    if (!Init::exists()) {
        cout << "FGit Repository has not been initialised! Aborting..." << endl;
        return;
    }

    if (subCmd == "log")
        Log::log();
    
    if (subCmd == "add"){
        Add add;
        if (argc == 2) {
            add.add();
        }
        else {
            add.add(argv[2]);
        }
    }
}

int main(int argc, char** argv) {
    if (argc >= 2) {
        string subcmd(argv[1]);
        runSubCmd(subcmd, argc ,argv);
    }

    return 0;
}
