#include "../include/Config.hpp"

int main(){
    Config config = Config();
    // Read directory targets for backup
    printf("Test: %s\n", config.getUserPath());
    if( Config::checkConfig() )
        config.parse_config_file();
    return 0;
}