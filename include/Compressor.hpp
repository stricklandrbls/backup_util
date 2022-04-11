#pragma once
#include "Content.hpp"
class Compressor{
    static inline void compress(Content* content_to_compress){

    };
    static inline void setDestination(std::string* path, std::string* hostname){
        Compressor::destination_path.path = path;
        Compressor::destination_path.hostname = hostname;
    };
    static inline std::string& getDestinationPath(){
        return *(Compressor::destination_path.path);
    };
    static inline std::string& getDestinationHostname(){
        return *(Compressor::destination_path.hostname);
    };
    private:
        static Destination destination_path;
};