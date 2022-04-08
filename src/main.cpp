#include "../include/Config.hpp"

int main(){
    Config config = Config();
    if( Config::checkConfig() )
        config.parse_config_file();
    return 0;
}