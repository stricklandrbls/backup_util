#pragma once
#include "Content.hpp"
#include "Config.hpp"
#include <zlib.h>
using content_it = std::vector<Content>::iterator;

struct thread_args{
    thread_args(std::vector<Content>* c, std::size_t lb, std::size_t ub): content_to_compress{ c }, lower_bound{ lb }, upper_bound{ ub }{};
    std::vector<Content>*   content_to_compress;
    size_t lower_bound;
    size_t upper_bound;
};

class Compressor{
    public:
        static inline void* compress_t(void* args){
            thread_args* thread_arguments = (thread_args*) args;
            std::unique_ptr<std::string> dest{new std::string(Compressor::getDestinationPath())};

            std::unique_ptr<std::string> command{new std::string};
            std::unique_ptr<std::string> dir{new std::string};
            std::unique_ptr<std::string> zip{new std::string};

            for(content_it it = thread_arguments->content_to_compress->begin() + thread_arguments->lower_bound; it != thread_arguments->content_to_compress->begin() + thread_arguments->upper_bound; it++)
            {
                *dir = std::get<Directory*>(*it)->_dirname();
                *zip = std::get<Directory*>(*it)->getZipFilePath();

                printf("compressing dir<%p>: %s\n", &(*it), (*dir).c_str());
                *command = "zip -rq -3 " + *dest + "/" + *dir + " " + *zip;
                #ifndef TEST
                system((*command).c_str());
                #endif
                Terminal::print(Terminal::success, *command);
            }
        };
        // static inline void compress(std::vector<Content>* content_to_compress, std::size_t& lb, std::size_t& mb, std::size_t& forks){
        //     if(fork() == 0){
        //         std::string command;
        //         for(content_it it = content_to_compress->begin(); it <= content_to_compress->begin() + lb; it++){
        //             printf("compressing dir<%p>: %s\n", std::get<Directory*>(*it), std::get<Directory*>(*it)->getZipFilePath().c_str());

        //             command = "zip -rq -3 ";
        //             command += Compressor::getDestinationPath();
        //             command += "/" + std::get<Directory*>(*it)->_dirname() + " " + std::get<Directory*>(*it)->getZipFilePath();
        //             #ifndef TEST
        //             system(command.c_str());
        //             #endif
        //             Terminal::print(Terminal::success, command);
        //         }
        //     }
        //     else{
        //         std::string command;
        //         for(content_it it = content_to_compress->begin() + mb; it != content_to_compress->end(); it++){
        //             printf("compressing dir<%p>: %s\n", std::get<Directory*>(*it), std::get<Directory*>(*it)->getZipFilePath().c_str());

        //             command = "zip -rq -3 ";
        //             command += Compressor::getDestinationPath();
        //             command += "/" + std::get<Directory*>(*it)->_dirname() + " " + std::get<Directory*>(*it)->getZipFilePath();
        //             #ifndef TEST
        //             system(command.c_str());
        //             #endif
        //             Terminal::print(Terminal::success, command);
        //         }
        //     }

        // };
        static inline void setDestination(std::string* path, std::string* host){
            Compressor::destination_path.path = path;
            Compressor::destination_path.hostname = host;
        };
        static inline std::string& getDestinationPath(){
            return *(Compressor::destination_path.path);
        };
        static inline std::string& getDestinationHostname(){
            return *(Compressor::destination_path.hostname);
        };
    protected:
        static inline Destination destination_path;
        static inline std::string zip_directory = "zip -r ";
        static inline std::string zip_file = "zip ";

};