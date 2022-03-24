#include "init.hpp"

#include "defaults.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

/**
 * @brief Checks if directory already exists
 *
 * @return If directory exists
 */
bool Init::exists() {
    return filesystem::is_directory(Defaults::fgitDirectory) && filesystem::exists(Defaults::fgitDirectory);
}

/**
 * @brief Creates all the necessary folder and files
 *
 * @return If file tree is successful
 */
bool Init::createTree() {
    if (!filesystem::create_directory(Defaults::fgitDirectory) ||
        !filesystem::create_directory(Defaults::fgitObjects) ||
        !filesystem::create_directory(Defaults::fgitRefs) ||
        !filesystem::create_directory(Defaults::fgitHeads))
        return false;

    return true;
}

/**
 * @brief Creates the .fgit directory used to store objects
 *
 * @return If the directory has been successfully created
 */
bool Init::init() {
    // Abort if directory already exists
    if (Init::exists()) {
        cout << "FGit Repository already initialised! Aborting..." << endl;
        return false;
    }

    // Create file structure
    if (!Init::createTree()) {
        cout << "FGit Repository could not be initialised! Aborting..." << endl;
        return false;
    }

    ofstream head(Defaults::fgitDirectory + "/HEAD");
    if (head.fail()) {
        cout << "FGit Repository could not be initialised! Aborting..." << endl;
        return false;
    }
    head << "master";
    head.close();

    cout << "FGit Repository initialised successfully!" << endl;
    return true;
}
