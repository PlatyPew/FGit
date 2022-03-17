#include "init.hpp"

#include <filesystem>
#include <iostream>

using namespace std;

const string Init::directory = ".fgit";

/**
 * @brief Checks if directory already exists
 *
 * @return If directory exists
 */
bool Init::exists() {
    return filesystem::is_directory(directory) && filesystem::exists(directory);
}

/**
 * @brief Creates the .fgit directory used to store objects
 *
 * @return If the directory has been successfully created
 */
bool Init::init() {
    // Abort if directory already exists
    if (Init::exists()) {
        cout << "Fake Git Repository already initialised!" << endl << "Aborting..." << endl;
        return false;
    }

    // Creates a new directory

    return true;
}
