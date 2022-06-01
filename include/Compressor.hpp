#pragma once
#include "Content.hpp"
#include "Config.hpp"
#include <zlib.h>
using content_it = std::vector<Content>::iterator;

struct Destination{
    Destination(const std::string& path, const std::string& host) : hostpath{ path }, hostname{ host }{};
    const std::string& hostpath;
    const std::string& hostname;
};
struct thread_args{
    thread_args(std::vector<Content>& c, std::size_t lb, std::size_t ub): content_to_compress{ c }, lower_bound{ lb }, upper_bound{ ub }{};
    std::vector<Content>&   content_to_compress;
    size_t lower_bound;
    size_t upper_bound;
};

class Compressor{
    public:
        static void* compress_t(void* args);

        static inline void setDestination(const std::string& path, const std::string& host){
            Compressor::destination_path = new Destination{path, host};
        };
        static inline const std::string& getDestinationPath(){ return Compressor::destination_path->hostpath; };
        static inline const std::string& getDestinationHostname(){ return Compressor::destination_path->hostname; };
        
    protected:
        static inline Destination* destination_path;
        static inline std::string zip_directory = "zip -r ";
        static inline std::string zip_file = "zip ";

};