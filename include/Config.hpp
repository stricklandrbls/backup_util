#pragma once
#include "common.hpp"
#include "json.hpp"
#include <cstdlib>

class Config{
    public:
        Config(){
            ENV_USER = std::getenv("USER");

        };
        ~Config(){};

        const char* getUserPath(){ return this->ENV_USER; }
        static bool checkConfig();
        void        parse_config_file();

    private:
        const char* ENV_USER;
        nlohmann::json  configData;

        
};