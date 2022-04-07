#pragma once

#include <stdio.h>
#include <map>
#include <string>

#include "Terminal.hpp"

#define CONFIG_PATH "/etc/backup-util/config.json"

struct Common{
    std::map<std::string, std::string> FS_DIRECTORIES;
    std::string dir_config = "";
};

class File{
    public:
        File(){};
        ~File(){};
        inline void     setFilename(std::string filename){ this->filename = filename; };
        inline void     setFilePtr(){ 
            // if(!this->filedata = fopen())
        };
    private:
        std::string path;
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