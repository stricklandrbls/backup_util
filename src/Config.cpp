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
    char c = input.get();

    while (input.good()){
        printf("%c", c);
        c = input.get();
    }

    input.close();
}