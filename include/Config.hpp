#pragma once
#include "common.hpp"
#include "Content.hpp"
#include "Compressor.hpp"
#include "json.hpp"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <memory>

using smart_string = std::unique_ptr<std::string>;
class Config{
    public:
        Config(){};
        ~Config(){};

        // std::vector<Directory*>*    getDirectories();
        // std::vector<File*>*         getFiles();
        std::vector<Content>*   getContent();

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

        // std::vector<Directory*>  directory_v;
        // std::vector<File*>       file_v;
        std::vector<Content>    content_v;

        nlohmann::json  configData;

        void (*type) (std::string);
        static inline void add(void (*type) (std::string, Config*), std::string path, Config* config){ type(path, config); };
        
        static inline void directory_type(std::string path, Config* config){
            smart_string output = std::make_unique<std::string>("Adding directory: ");
            *output += path;
            Terminal::print(Terminal::info, *output);

            Directory* entry = new Directory(path);

            if(entry->isValid(path))
                config->content_v.push_back(entry);
            else
                delete(entry);
        };
        static inline void file_type(std::string path, Config* config){
            smart_string output = std::make_unique<std::string>("Adding directory: ");
            *output += path;
            Terminal::print(Terminal::info, *output);

            File* entry = new File(path);

            if(entry->isValid(path))
                config->content_v.push_back(entry);
            else
                delete(entry);
        };

};