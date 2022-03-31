#include "log.hpp"
#include "commit.hpp"
#include "defaults.hpp"

#include <fstream>
#include <iostream>

using namespace std;

void Log::print(Commit commit) {
    cout << "commit: " << commit.getId() << endl;
    cout << "Author: " << commit.getAuthor() << endl;
    cout << "Message: " << commit.getMessage() << endl;
}

void Log::log() {
    Log::log(Commit::getHeadCommit());
}

void Log::log(string id) {
    Commit c;
    ifstream in;

    do {
        in.open(Defaults::fgitObjects + id);
        in >> c;
        in.close();
        Log::print(c);
    } while ((id = c.getPrevId()) != "");
}
