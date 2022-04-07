#include "diff.hpp"
#include "init.hpp"
#include "log.hpp"
#include "reset.hpp"
#include "status.hpp"

using namespace std;

void runSubCmd(string subCmd, int argc, char** argv) {
    // fgit init
    if (subCmd == "init") {
        Init::init();
        return;
    }
    // Check if .fgit exists
    if (!Init::exists())
        throw "FGit Repository has not been initialised";

    if (subCmd == "status") {
        Status::status();
        return;
    }

    // fgit log
    if (subCmd == "log") {
        Log::log();
        return;
    }

    // fgit diff
    if (subCmd == "diff") {
        Diff::diff();
        return;
    }

    // fgit reset [commit hash]
    if (subCmd == "reset") {
        switch (argc) {
        case 2:
            Reset::reset();
            break;

        case 3:
            Reset::reset(argv[2]);
            break;

        default:
            throw "Too many arguments";
        }
    }
}

int main(int argc, char** argv) {
    if (argc >= 2) {
        string subcmd(argv[1]);
        try {
            runSubCmd(subcmd, argc, argv);
        } catch (const string msg) {
            cerr << msg << endl;
        }
    }

    return 0;
}
