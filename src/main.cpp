#include "../include/Config.hpp"
#include "../include/common.hpp"
#include "../include/Content.hpp"

int main(){
    Config config = Config();

    if( Config::checkConfig() )
        config.parse_config_file();
    
    Compressor::setDestination(config.getOutputPath_p(), config.getOutputHost_p());
    
    std::vector<Directory*>*    dir_to_compress = config.getDirectories();
    std::vector<File*>*         file_to_compress = config.getFiles();

    std::string command;
    for(auto* dir : *dir_to_compress){

        command = "zip -rv -7 ";
        command += Compressor::getDestinationPath();
        command += "/" + dir->_dirname() + " " + dir->getPath();
        system(command.c_str());
        Terminal::print(Terminal::success, command);        
    }
    return 0;
}