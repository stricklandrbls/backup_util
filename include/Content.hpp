#pragma once
#include "common.hpp"
#include <vector>
#include <dirent.h>
// #include <openssl/sha.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
class Content{
    public:
        Content(){};
        ~Content(){};
    protected:
        std::string path;
        std::vector<std::string> contents;
        std::string hash;

        static const int K_READ_BUF_SIZE{ 1024 * 16 };

        virtual bool isValid(std::string* path);
        
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

    protected:
        bool isValid(std::string* path) override{
            if( !(this->filedata = fopen(path->c_str(), "r")) ){
                return false;
            }
            fclose(filedata);
            return true;
        }

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
                // pullContentsFromPath();
            }

        };
        ~Directory(){};
    protected:
        bool isValid(std::string* path) override{
            if( !(this->dir = opendir(path->c_str())))
                return false;
            closedir(this->dir);
            return true;
        };

    private:
        DIR*        dir;
        std::string dirname;
        

        inline void pullDirnameFromPath(){
            this->dirname = this->path.substr(this->path.find_last_of("/"));
        };
        inline void pullContentsFromPath(){
            dirent* dir_info = readdir(this->dir);

        };
};

struct Destination{
    std::string* path;
    std::string* hostname;
};