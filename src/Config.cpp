#include "../include/Config.hpp"
#include <iostream>
#include <fstream>

bool Config::checkConfig(){
    FILE* configFile;
    Terminal::print(Terminal::info, "Checking config file...");

    if( !(configFile = fopen(CONFIG_PATH, "r")) ){
        Terminal::print(Terminal::err, "Error opening config file!");
        return false;
    }

    return true;
}

void Config::parse_config_file(){
    std::ifstream input(CONFIG_PATH, std::ifstream::in);
    nlohmann::json configData;

    input >> configData;

    for(nlohmann::json::iterator it = configData.begin(); it != configData.end(); it++){

        if(it.key() == var::DIR){
            for(auto data : *it)
                Config::add(Config::directory_type, data, this);
        }
        if(it.key() == var::FILE){
            for (auto data : *it)
                Config::add(Config::file_type, data, this);
        }
        if(it.key() == var::DEST){
            std::cout << it.value() << std::endl;
        }
        
    }
    input.close();
}