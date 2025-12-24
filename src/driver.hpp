#pragma once

#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

class Driver {
  private:
    struct file {
        std::string path;
        std::string root;
        std::string parent;
        std::string stem;
        std::string input;
        std::string preprocessed;
        std::string assembly;
        std::string object;
        std::string output;
    } file;

    struct options {
        bool preprocess;
        bool assemble;
        bool compile;
    } options;

  public:
    Driver( std::string file_path ) {
        std::filesystem::path path_data = file_path.data();
        if ( path_data.extension() == ".c" ) {
            std::cerr << path_data.stem() << " is a valid file type.\n";
        } else {
            std::cerr << path_data.stem() << " is an invalid file type.\n";
            throw;
        }
        std::string stem = path_data.stem();
        std::cerr << stem << "\n";

        file.stem         = stem;
        file.preprocessed = stem;
        file.assembly     = stem;
        file.object       = stem;
        file.input        = stem;
        file.output       = stem;
        file.root         = path_data.root_path();
        file.parent       = path_data.parent_path();
        file.path         = file.root + file.parent + "/";

        file.input += ".c";
        file.preprocessed += ".i";
        file.assembly += ".s";
        file.object += ".o";

        options.preprocess = true;
        options.assemble   = true;
        options.compile    = true;

        std::string command = "clang ";
        std::string input   = file.path + file.input;
        std::string output  = file.path + file.output;
        command += input;
        command += " -o ";
        command += output;

        std::system( command.c_str() );
    }
};
