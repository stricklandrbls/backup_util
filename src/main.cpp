#include "../include/Config.hpp"
#include "../include/common.hpp"
#include "../include/Content.hpp"


int main(){
    Config config = Config();
    if( Config::checkConfig() )
        config.parse_config_file();
    
    
    return 0;
}