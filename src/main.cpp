#include "../include/Config.hpp"
#include "../include/common.hpp"
#include "../include/Content.hpp"
#include "../include/ConfigData.hpp"

#include <pthread.h>

int main(){
    Config config = Config();
    ConfigData config_data{};
    config_data.printAll();

    if( Config::checkConfig() )
        config.parse_config_file();
    
    Compressor::setDestination(config.getOutputPath_p(), config.getOutputHost_p());
    std::string output = "Compressor destination: " + Compressor::getDestinationPath();
    Terminal::print(Terminal::success, output);
    
    // std::vector<Content>*    content_to_compress = &(Config::content_v);

    std::string command;
    std::size_t forks = Config::content_v.size() / 2;
    
    std::size_t middle_bound;
    (Config::content_v.size() % 2 == 0)? middle_bound = Config::content_v.size() / 2 : middle_bound = (Config::content_v.size() / 2) + 1;

    pthread_t thread1, thread2;
    thread_args args1{&Config::content_v, 0, middle_bound};
    thread_args args2{&Config::content_v, middle_bound, Config::content_v.size()};

    pthread_create(&thread1, NULL, Compressor::compress_t, &args1);
    pthread_create(&thread2, NULL, Compressor::compress_t, &args2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Compressor::compress(content_to_compress, lb, mb, forks);
    return 0;
}

