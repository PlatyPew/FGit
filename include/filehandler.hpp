#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Filehandler {
  public:
    /**
     * @brief check if the file is binary
     *
     * @param filename: file to check
     * @return true if binary file
     */
    static bool isBinary(std::string filename) {
        if (!exists(filename))
            throw "File not found";

        int c;
        std::ifstream ifs(filename, std::ios::binary);
        while ((c = ifs.get()) != EOF && c <= 127)
            ;
        if (c == EOF)
            return false;

        return true;
    }

    /**
     * @brief Checks if file exists
     *
     * @param filename: file to check
     * @return true if file found
     */
    static bool exists(std::string filename) {
        return std::filesystem::exists(filename);
    }

    /**
     * @brief read files
     *
     * @param filename: file to read
     * @return contents of the file
     */
    static std::string read(std::string filename) {
        if (!exists(filename))
            throw "File not found";

        std::ifstream in(filename, std::ios::binary);
        std::stringstream data;

        data << in.rdbuf();
        in.close();

        return data.str();
    }

    /**
     * @brief write contents to the file
     *
     * @param filename: file to write
     * @param contents: contents to write to file
     */
    static void write(std::string filename, std::string contents) {
        std::ofstream out;
        if (!out)
            throw "Cannot open file!";

        out.open(filename, std::ios::binary);
        out << contents;
        out.close();
    }
};
