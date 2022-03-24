#include "diff.hpp"
#include "init.hpp"

#include "blob.hpp"
#include "commit.hpp"

#include <iostream>
#include <vector>

using namespace std;

void runSubCmd(string subCmd) {
    if (subCmd == "init")
        Init::init();
}

int main(int argc, char** argv) {
    if (argc >= 2) {
        string subcmd(argv[1]);

        runSubCmd(subcmd);
    }

    Blob blob("./CMakeLists.txt");
    createBlob(blob);

    vector<Blob> blobs;
    blobs.push_back(blob);

    Commit commit(blobs, "Platy", "Initial Commit");
    createCommit(commit);

    cout << commit;

    return 0;
}
