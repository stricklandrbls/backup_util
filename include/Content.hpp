#pragma once
#include "common.hpp"
#include <vector>
#include <dirent.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>
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
        void        setZipFilePath(const std::string& data);
        bool        isValid(const std::string& path);

        // Header defined functions
        // std::string     getPath(){ return this->path; };
        // std::string&    getZipFilePath(){ return this->zip_path; };
        std::string        getPath(){ return this->file_path.string(); }
        std::string        getZipFilePath(){ return this->zip_path.string(); }


        // Inhieritance Functions
        // virtual bool    isValid(std::string* path) = 0;

        // Currently unused
        // std::string     getHash(){ return this->hash; };

    protected:
        // std::string path;
        // std::string zip_path;
        path file_path;
        path zip_path;

        // Currently Unused
        // std::vector<std::string> contents;
        // std::string hash;
};

class File : public ContentBase{
    public:
        // File(std::string file_path): file_path{ file_path }; 

        File(std::string path){
            if(isValid(path));
                // this->hash = this->calculateHash(path);
        };
        
        ~File(){};

        File& operator=(const File& copy){ return *this; };

    protected:

    private:
        std::string filename;
        FILE*       filedata;
        

};

class Directory : public ContentBase{
    public:
        Directory(std::string path){
            if(isValid(path)){
                this->file_path= path;
                setZipFilePath(this->file_path.string());
                pullDirnameFromPath();
                setParentDirPath();
            }

        };
        ~Directory(){};
        std::string    _dirname(){ return this->dirname; };
        std::string*    _parent_dir_path(){ return &(this->parent_dir_path); };

    protected:

    private:
        DIR*        dir;
        std::string dirname;
        std::string parent_dir_path;
        
        void pullDirnameFromPath();
        void setParentDirPath();
};

struct Destination{
    std::string* path;
    std::string* hostname;
};

using Content = std::variant<Directory*, File*>;