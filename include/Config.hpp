#pragma once
#include "common.hpp"
#include "Content.hpp"
#include "Compressor.hpp"
#include "json.hpp"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>

class Config{
    public:
        Config(){};
        ~Config(){};

        std::vector<Content>*   getContent();

        static bool checkConfig();

        void        parse_config_file();
        std::string getOutputPath();
        std::string getOutputHost();
        std::string*    getOutputPath_p();
        std::string*    getOutputHost_p();
        void setOutputPath(std::string path);
        void setOutputHost(std::string host);

        static inline std::vector<Content>    content_v;

    private:
        std::string output_path;
        std::string output_host;


        nlohmann::json  configData;

        void (*type) (std::string);

        // Removed statics, not being used
        static inline void add(void (*type) (std::string, Config*), std::string path, Config* config){ type(path, config); };
        
        static void directory_type(std::string path, Config* config){
            smart_string output = std::make_unique<std::string>("Adding directory: ");
            *output += path;
            Logger::tprint(Logger::LEVEL::INFO, *output);

            Directory* entry = new Directory(path);

            if(entry->isValid(path))
                Config::content_v.push_back(entry);
            else
                delete(entry);
        };
        static inline void file_type(std::string path, Config* config){
            smart_string output = std::make_unique<std::string>("Adding directory: ");
            *output += path;
            Logger::tprint(Logger::LEVEL::INFO, *output);

            File* entry = new File(path);

            if(entry->isValid(path))
                Config::content_v.push_back(entry);
            else
                delete(entry);
        };

};