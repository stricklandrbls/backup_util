
#include "../include/Compressor.hpp"

void* Compressor::compress_t(void* args){
    thread_args* thread_arguments = (thread_args*) args;

    // smart_string dest{new std::string(Compressor::getDestinationPath())};
    smart_string dest{std::make_unique<std::string>(Compressor::getDestinationPath())};

    std::shared_ptr<std::string> command{std::make_shared<std::string>("")};
    
    smart_string dir{std::make_unique<std::string>("")};
    smart_string zip{std::make_unique<std::string>("")};
    smart_string path{std::make_unique<std::string>("")};

    std::cout << "Compressing with bounds: [" << thread_arguments->lower_bound << ":" << thread_arguments->upper_bound << "]" << std::endl;

    for(content_it  it = thread_arguments->content_to_compress.begin() + thread_arguments->lower_bound; 
                    it != thread_arguments->content_to_compress.begin() + thread_arguments->upper_bound; 
                    it++)
    {
        *dir = std::get<Directory*>(*it)->_dirname();
        *zip = std::get<Directory*>(*it)->getZipFilePath();
        *path = std::get<Directory*>(*it)->getPath();
        printf("compressing dir<%p>: %s\n", &(*it), (*dir).c_str());
        *command = "zip -rq -3 " + *dest + "/" + *dir + ".zip " + *path;
        #ifndef TEST
        system((*command).c_str());
        #endif
        Logger::print(Logger::LEVEL::SUCCESS, *command);
    }
    // delete thread_arguments;
    return 0;
}