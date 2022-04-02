#include "log.hpp"
#include "commit.hpp"
#include "defaults.hpp"

#include <fstream>
#include <iostream>

using std::cout, std::endl, std::ifstream, std::string;

void Log::print(Commit commit) {
    cout << "commit: " << commit.getId() << endl;
    cout << "Author: " << commit.getAuthor() << endl;
    cout << "Message: " << commit.getMessage() << endl;
}

void Log::log() {
    Log::log(Commit::getHeadCommit());
}

void Log::log(string id) {
    if (Commit::isGenesis())
        return;

    Commit c;
    ifstream in;

    do {
        in.open(Defaults::fgitObjects + id);
        in >> c;
        in.close();
        Log::print(c);
    } while ((id = c.getPrevId()) != "");
}
