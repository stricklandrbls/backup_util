#pragma once
#include "common.hpp"
#include <vector>
#include <dirent.h>

class File{
    public:
        File(std::string path){
            isValid(&path);
        };
        ~File(){};
    private:
        std::vector<std::string> files;
        std::string path;
        std::string filename;
        FILE*       filedata;
        
        inline bool isValid(std::string* path){
            if( !(this->filedata = fopen(path->c_str(), "r")) ){
                return false;
            }
            fclose(filedata);
            return true;
        }
};

class Directory{
    public:
        Directory(std::string path){
            if(isValid(&path)){
                this->path = path;
                pullDirnameFromPath();
                // pullContentsFromPath();
            }

        };
        ~Directory(){};
    private:
        std::vector<std::string> contents;
        DIR*        dir;
        std::string path;
        std::string dirname;
        

        inline void pullDirnameFromPath(){
            this->dirname = this->path.substr(this->path.find_last_of("/"));
        };
        inline void pullContentsFromPath(){
            dirent* dir_info = readdir(this->dir);

        };
        inline bool isValid(std::string* path){
            if( !(this->dir = opendir(path->c_str())))
                return false;
            closedir(this->dir);
            return true;
        };
};

struct{
    std::string path;
    std::string hostname;
} Destination;