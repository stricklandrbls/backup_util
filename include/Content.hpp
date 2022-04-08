#pragma once
#include "common.hpp"
#include <vector>
#include <dirent.h>

class File{
    public:
        File(){};
        ~File(){};
        inline void     setFilename(std::string filename){ this->filename = filename; };
        inline void     setFilePtr(){ };
    private:
        std::string path;
        std::string filename;
        FILE*       filedata;
        
};

class Directory{
    public:
        Directory(std::string path){
            this->path = path;
            pullDirnameFromPath();

        }
        ~Directory(){};
    private:
        std::vector<File*> contents;
        std::string path;
        std::string dirname;

        inline void pullDirnameFromPath(){
            std::string ret = this->path.substr(this->path.find_last_of("/"));
        };
        inline void pullContentsFromPath(){
            
        };
};