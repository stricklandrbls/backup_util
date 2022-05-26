
#include "../include/Compressor.hpp"

void* Compressor::compress_t(void* args){
    thread_args* thread_arguments = (thread_args*) args;

    smart_string dest{new std::string(Compressor::getDestinationPath())};
    smart_string command{new std::string};
    smart_string dir{new std::string};
    smart_string zip{new std::string};

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
}