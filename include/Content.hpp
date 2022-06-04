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

        void        setZipFilePath(const std::string& data);
        bool        isValid(const std::string& path);

        std::string        getPath(){ return this->file_path.string(); }
        std::string        getZipFilePath(){ return this->zip_path.string(); }

    protected:
        path file_path;
        path zip_path;
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
        // Default Constructor
        Directory(std::string path){
            if(std::filesystem::exists(static_cast<std::filesystem::path>(path))){
                this->file_path = path;
                setZipFilePath(this->file_path.string());
                pullDirnameFromPath();
                setParentDirPath();
            }
        };

        // Move Constructor
        // Directory(Directory&& move_from){

        // };

        // Copy Constructor
        // Directory(Directory& copy_from){

        // };

        // Move Assignment Operator
        // Directory& operator=(Directory&& move_from){

        // };

        // Copy Assignment Operator
        // Directory& operator=(Directory& copy_from){

        // }

        std::string    _dirname(){ return this->dirname; };
        std::string*    _parent_dir_path(){ return &(this->parent_dir_path); };

    protected:

    private:
        std::string parent_dir_path;
        std::string dirname;
        std::filesystem::directory_entry dir;
        
        void pullDirnameFromPath();
        void setParentDirPath();
};



using Content = std::variant<Directory*, File*>;