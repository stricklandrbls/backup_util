#pragma once
#include "common.hpp"
#include <vector>
#include <dirent.h>
// #include <openssl/sha.h>
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
class Content{
    public:
        Content(){};
        ~Content(){};
        std::string    getPath(){ return this->path; };
        std::string    getHash(){ return this->hash; };

        virtual bool isValid(std::string* path){return false;};
    protected:
        std::string path;
        std::vector<std::string> contents;
        std::string hash;

        static const int K_READ_BUF_SIZE{ 1024 * 16 };

        
        // inline std::string calculateHash(std::string filename)
        // {
        //     // Initialize openssl
        //     SHA256_CTX context;
        //     if(!SHA256_Init(&context))
        //     {
        //         return nullptr;
        //     }

        //     // Read file and update calculated SHA
        //     char buf[K_READ_BUF_SIZE];
        //     std::ifstream file(filename, std::ifstream::binary);
        //     while (file.good())
        //     {
        //         file.read(buf, sizeof(buf));
        //         if(!SHA256_Update(&context, buf, file.gcount()))
        //         {
        //             return nullptr;
        //         }
        //     }

        //     // Get Final SHA
        //     unsigned char result[SHA256_DIGEST_LENGTH];
        //     if(!SHA256_Final(result, &context))
        //     {
        //         return nullptr;
        //     }

        //     // Transform byte-array to string
        //     std::stringstream shastr;
        //     shastr << std::hex << std::setfill('0');
        //     for (const auto &byte: result)
        //     {
        //         shastr << std::setw(2) << (int)byte;
        //     }
        //     return shastr.str();
        // }
};

class File : public Content{
    public:
        File(std::string path){
            if(isValid(&path));
                // this->hash = this->calculateHash(path);
        };
        ~File(){};

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

class Directory : public Content{
    public:
        Directory(std::string path){
            if(isValid(&path)){
                this->path = path;
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
            this->dirname = this->path.substr(this->path.find_last_of("/"));
        };
        void setParentDirPath(){
            this->parent_dir_path = this->path.substr(0, this->path.find_last_of("/"));
        }
};

struct Destination{
    std::string* path;
    std::string* hostname;
};