#pragma once
#include "Content.hpp"
#include "Config.hpp"
#include <zlib.h>

class Compressor{
    public:
        static inline void compress(Content* content_to_compress){

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