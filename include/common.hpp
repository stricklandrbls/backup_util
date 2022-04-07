#pragma once

#include <stdio.h>
#include <map>
#include <string>

#include "Terminal.hpp"

#define CONFIG_PATH "/etc/backup-util/config.json"

typedef struct Common{
    std::map<std::string, std::string> FS_DIRECTORIES;
    std::string dir_config = "";
};

class File{
    public:
    private:
        std::string filename;
        // Directory dirname;
        FILE*       filedata;
        
};

class Directory{
    public:
        Directory(){};
        ~Directory(){};
    private:
        std::string path;
        std::string dirname;
};