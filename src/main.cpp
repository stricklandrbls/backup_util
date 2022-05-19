#include "../include/Config.hpp"
#include "../include/common.hpp"
#include "../include/Content.hpp"
#include <pthread.h>

int main(){
    Config config = Config();

    if( Config::checkConfig() )
        config.parse_config_file();
    
    Compressor::setDestination(config.getOutputPath_p(), config.getOutputHost_p());
    std::string output = "Compressor destination: " + Compressor::getDestinationPath();
    Terminal::print(Terminal::success, output);
    
    std::vector<Content>*    content_to_compress = config.getContent();

    std::string command;
    std::size_t forks = content_to_compress->size() / 2;
    
    std::size_t middle_bound;
    (content_to_compress->size() % 2 == 0)? middle_bound = content_to_compress->size() / 2 : middle_bound = (content_to_compress->size() / 2) + 1;

    pthread_t thread1, thread2;
    thread_args args1{content_to_compress, 0, middle_bound};
    thread_args args2{content_to_compress, middle_bound, content_to_compress->size()};

    pthread_create(&thread1, NULL, Compressor::compress_t, &args1);
    pthread_create(&thread2, NULL, Compressor::compress_t, &args2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Compressor::compress(content_to_compress, lb, mb, forks);
    return 0;
}

