#include "../include/Config.hpp"
#include "../include/common.hpp"
#include "../include/Content.hpp"

int main(){
    Config config = Config();

    if( Config::checkConfig() )
        config.parse_config_file();
    
    Compressor::setDestination(config.getOutputPath_p(), config.getOutputHost_p());
    std::string output = "Compressor destination: " + Compressor::getDestinationPath();
    Terminal::print(Terminal::success, output);
    
    std::vector<Content>*    content_to_compress = config.getContent();

    std::string command;
    std::size_t forks = content_to_compress->size() / 2;
    
    std::size_t lb, mb;
    if(forks % 2 != 0){
        lb = forks;
        mb = forks + 1;
    }
    else{
        lb = forks -1;
        mb = forks;
    }
    Compressor::compress(content_to_compress, lb, mb, forks);
    return 0;
}

