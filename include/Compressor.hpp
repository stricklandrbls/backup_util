#pragma once
#include "Content.hpp"
#include "Config.hpp"
#include <zlib.h>

class Compressor{
    public:
        static inline void compress(std::vector<Directory*>* content_to_compress, std::size_t& lb, std::size_t& mb, std::size_t& forks){
            if(fork() == 0){
                std::string command;
                for(std::vector<Directory*>::iterator it = content_to_compress->begin(); it <= content_to_compress->begin() + lb; it++){
                    printf("compressing dir<%p>: %s\n", *it, (*it)->getPath().c_str());

                    command = "zip -rv -7 ";
                    command += Compressor::getDestinationPath();
                    command += "/" + (*it)->_dirname() + " " + (*it)->getPath();
                    #ifndef TEST
                    system(command.c_str());
                    #endif
                    Terminal::print(Terminal::success, command);
                }
            }
            else{
                std::string command;
                for(std::vector<Directory*>::iterator it = content_to_compress->begin() + mb; it != content_to_compress->end(); it++){
                    printf("compressing dir<%p>: %s\n", *it, (*it)->getPath().c_str());

                    command = "zip -rv -7 ";
                    command += Compressor::getDestinationPath();
                    command += "/" + (*it)->_dirname() + " " + (*it)->getPath();
                    #ifndef TEST
                    system(command.c_str());
                    #endif
                    Terminal::print(Terminal::success, command);
                }
            }

        };
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