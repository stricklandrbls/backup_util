#pragma once
#include "common.hpp"
#include "Content.hpp"
#include "Compressor.hpp"
#include "json.hpp"
#include <cstdlib>
#include <vector>
#include <iostream>
class Config{
    public:
        Config(){};
        ~Config(){};

        std::vector<Directory*>*    getDirectories();
        std::vector<File*>*         getFiles();

        static bool checkConfig();

        void        parse_config_file();
        std::string getOutputPath();
        std::string getOutputHost();
        std::string*    getOutputPath_p();
        std::string*    getOutputHost_p();
        void setOutputPath(std::string path);
        void setOutputHost(std::string host);

    protected:

    private:
        std::string output_path;
        std::string output_host;

        std::vector<Directory*>  directory_v;
        std::vector<File*>       file_v;
        nlohmann::json  configData;

        void (*type) (std::string);
        static inline void directory_type(std::string path, Config* config){
            std::string output = "Adding directory: ";
            output += path;
            Terminal::print(Terminal::info, output);
            config->directory_v.push_back(new Directory(path));
        };
        static inline void file_type(std::string path, Config* config){
            std::string output = "Adding file: ";
            output += path;
            config->file_v.push_back(new File(path));
        };
        static inline void add(void (*type) (std::string, Config*), std::string path, Config* config){ type(path, config); };

};