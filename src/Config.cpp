#include "../include/Config.hpp"
using namespace nlohmann;

bool Config::checkConfig(){
    // FILE* configFile;
    path configFile = CONFIG_PATH;
    Terminal::print(Terminal::info, "Checking config file...");

    // if( !(configFile = fopen(CONFIG_PATH, "r")) ){
    //     Terminal::print(Terminal::err, "Error opening config file!");
    //     return false;
    // }

    if(!std::filesystem::exists(configFile) || !std::filesystem::is_regular_file(configFile)){
        Terminal::print(Terminal::err, "Error opening config file!");
        return false; 
    }

    return true;
}

void Config::parse_config_file(){
    std::ifstream   input(CONFIG_PATH, std::ifstream::in);
    json  configData;

    input >> configData;

    for(json::iterator it = configData.begin(); it != configData.end(); it++){
        
        if(it.key() == var::DIR){
            for(std::string data : *it){
                Config::add(Config::directory_type, data, this);
            }
        }
        if(it.key() == var::FILE){
            for (std::string data : *it){
                Config::add(Config::file_type, data, this);
            }
        }
        if(it.key() == var::DEST){
            std::string output = "Setting HOST | PATH: ";
            output += it.value()[var::HOST];
            output += " | ";
            output += it.value()[var::PATH_D];
            Terminal::print(Terminal::info, output);

            this->output_host = it.value()[var::HOST];
            this->output_path = it.value()[var::PATH_D];
        }
        
    }
    input.close();
}


std::string     Config::getOutputPath()     { return this->output_path; }
std::string*    Config::getOutputPath_p()   { return &(this->output_path); }
std::string     Config::getOutputHost()     { return this->output_host; }
std::string*    Config::getOutputHost_p()   { return &(this->output_host); }

// std::vector<std::variant<Directory*, File*>>*    Config::getContent(){ return &(Config::content_v); }

void Config::setOutputHost(std::string host){ this->output_host = host; }
void Config::setOutputPath(std::string path){ this->output_path = path; }