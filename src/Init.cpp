#include "init.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

const string Init::directory = ".fgit";
const string Init::objects = "objects";
const string Init::refs = "refs";
const string Init::heads = "heads";

/**
 * @brief Checks if directory already exists
 *
 * @return If directory exists
 */
bool Init::exists() {
    return filesystem::is_directory(directory) && filesystem::exists(directory);
}

/**
 * @brief Creates all the necessary folder and files
 *
 * @return If file tree is successful
 */
bool Init::createTree() {
    if (!filesystem::create_directory(directory) ||
        !filesystem::create_directory(directory + "/" + objects) ||
        !filesystem::create_directory(directory + "/" + refs) ||
        !filesystem::create_directory(directory + "/" + refs + "/" + heads))
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

    ofstream head(directory + "/HEAD");
    if (head.fail()) {
        cout << "FGit Repository could not be initialised! Aborting..." << endl;
        return false;
    }
    head << "master: ";
    head.close();

    cout << "FGit Repository initialised successfully!" << endl;
    return true;
}
