#include "log.hpp"
#include "commit.hpp"
#include "defaults.hpp"

#include <fstream>
#include <iostream>

using std::cout, std::endl, std::ifstream, std::string;

/**
 * @brief prints out commit log
 *
 * @param commit: commit to read from
 */
void Log::print(Commit commit) {
    cout << "Commit: " << commit.getId();

    if (commit.getId() == Commit::getHeadCommit())
        cout << " <--- HEAD";
    cout << endl;

    cout << "Timestamp: " << commit.getTimestamp() << endl;
    cout << "Author: " << commit.getAuthor() << endl;
    cout << "Message: " << commit.getMessage() << endl;

    if (commit.getPrevId() != "")
        cout << endl;
}

/**
 * @brief get commit log from latest
 *
 */
void Log::log() {
    Log::log(Commit::getLatestCommit());
}

/**
 * @brief get commit log from commit id
 *
 * @param id: commit id
 */
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
