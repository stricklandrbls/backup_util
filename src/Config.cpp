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
    std::ifstream   input(CONFIG_PATH, std::ifstream::in);
    nlohmann::json  configData;

    input >> configData;

    for(nlohmann::json::iterator it = configData.begin(); it != configData.end(); it++){
        auto cleanse = [&](std::string data){
            while(data.find(" ")){
                data.replace(data.find(" "), 1, "\\ ");
            }
        };
        
        cleanse(*it);
        if(it.key() == var::DIR){
            for(auto data : *it)
                Config::add(Config::directory_type, data, this);
        }
        if(it.key() == var::FILE){
            for (auto data : *it)
                Config::add(Config::file_type, data, this);
        }
        if(it.key() == var::DEST){
            std::string output = "Setting HOST | PATH: ";
            output += it.value()[var::HOST];
            output += " | ";
            output += it.value()[var::PATH_D];
            Terminal::print(Terminal::info, output);

            setOutputHost(it.value()[var::HOST]);
            setOutputPath(it.value()[var::PATH_D]);
        }
        
    }
    input.close();
}

std::string Config::getOutputPath(){ return this->output_path; }
std::string* Config::getOutputPath_p(){ return &(this->output_path); }
std::string Config::getOutputHost(){ return this->output_host; }
std::string* Config::getOutputHost_p(){ return &(this->output_host); }

std::vector<Directory*>*    Config::getDirectories(){ return &(this->directory_v); }
std::vector<File*>*         Config::getFiles(){ return &(this->file_v); }

void Config::setOutputHost(std::string host){ this->output_host = host; }
void Config::setOutputPath(std::string path){ this->output_path = path; }