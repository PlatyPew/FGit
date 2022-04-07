#include "diff.hpp"
#include "init.hpp"
#include "log.hpp"
#include "reset.hpp"
#include "status.hpp"

using namespace std;

map<string, pair<bool, bool>> commitHandler(int argc, char** argv) {
    map<string, pair<bool, bool>> commitable = Status::checkThrough();

    map<string, pair<bool, bool>> toCommit;
    for (int i = 4; i < argc; i++) {
        string file = argv[i];

        if (!commitable.count(file))
            throw "File cannot be commited!";

        pair<bool, bool> stage = commitable.at(file);
        toCommit.insert(pair<string, pair<bool, bool>>(file, stage));
    }

    return toCommit;
}

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

    // fgit commit <author> <message> [files]
    if (subCmd == "commit") {
        if (argc < 5)
            throw "Not enough arguments!";

        string author = argv[2];
        string message = argv[3];

        Commit::commit(commitHandler(argc, argv), author, message);
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
        return;
    }

    throw "Subcommand does not exist!";
}

int main(int argc, char** argv) {
    if (argc >= 2) {
        string subcmd(argv[1]);
        try {
            runSubCmd(subcmd, argc, argv);
        } catch (const char* msg) {
            cerr << msg << endl;
        }
    } else {
        cout << "Subcommands available: init, status, log, diff, commit, reset" << endl;
    }

    return 0;
}
