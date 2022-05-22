#pragma once
#include "common.hpp"
#include <vector>
#include <dirent.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

/* CONST VARIABLES */
namespace var{
    const std::string DIR = "directories";
    const std::string FILE = "files";
    const std::string DEST = "destination";
    const std::string HOST = "hostname";
    const std::string LOCAL = "local";
    const std::string PATH_D = "path";
}

namespace network{
    const int PORT = 16969;
}

using path = std::filesystem::path;

class ContentBase{
    public:
        ContentBase(){};
        ~ContentBase(){};

        // Forward declarations
        void            setZipFilePath(std::string* data);

        // Header defined functions
        std::string     getPath(){ return this->path; };
        std::string&    getZipFilePath(){ return this->zip_path; };

        // Inhieritance Functions
        virtual bool    isValid(std::string* path) = 0;

        // Currently unused
        // std::string     getHash(){ return this->hash; };

    protected:
        std::string path;
        std::string zip_path;

        // Currently Unused
        // std::vector<std::string> contents;
        // std::string hash;
};

class File : public ContentBase{
    public:
        File(std::string path){
            if(isValid(&path));
                // this->hash = this->calculateHash(path);
        };
        
        ~File(){};

        File& operator=(const File& copy){ return *this; };

        bool isValid(std::string* path) override{
            if( !(this->filedata = fopen(path->c_str(), "r")) ){
                return false;
            }
            fclose(filedata);
            return true;
        }

    protected:

    private:
        std::string filename;
        FILE*       filedata;
        

};

class Directory : public ContentBase{
    public:
        Directory(std::string path){
            if(isValid(&path)){
                this->path = path;
                setZipFilePath(&(this->path));
                pullDirnameFromPath();
                setParentDirPath();
                // pullContentsFromPath();
            }

        };
        ~Directory(){};
        std::string    _dirname(){ return this->dirname; };
        std::string*    _parent_dir_path(){ return &(this->parent_dir_path); };
        bool isValid(std::string* path) override{
            if( !(this->dir = opendir(path->c_str()))){
                std::string output = "Directory not valid: ";
                output += *path;
                Terminal::print(Terminal::err, output);

                return false;
            }
            closedir(this->dir);
            return true;
        };

    protected:

    private:
        DIR*        dir;
        std::string dirname;
        std::string parent_dir_path;
        
        inline void pullDirnameFromPath(){
            this->dirname = this->zip_path.substr(this->zip_path.find_last_of("/") + 1);
        };
        void setParentDirPath(){
            this->parent_dir_path = this->path.substr(0, this->path.find_last_of("/"));
        }
};

struct Destination{
    std::string* path;
    std::string* hostname;
};

using Content = std::variant<Directory*, File*>;