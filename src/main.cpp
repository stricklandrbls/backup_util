#include "../include/Config.hpp"
#include "../include/common.hpp"
#include "../include/Content.hpp"
#include "../include/ConfigData.hpp"

#include <pthread.h>

int main(){
    ConfigData config_data{};
    std::vector<Content>&  content = config_data.content();
    printf("1\n");
    Compressor::setDestination(config_data.destination_hostpath(), config_data.destination_hostname());
printf("2\n");
    Terminal::print(Terminal::success, "Compressor destination: " + Compressor::getDestinationPath());
    printf("3\n");
    std::size_t middle_bound;
    size_t      content_length = content.size();
printf("4\n");
    (content_length % 2 == 0)? middle_bound = content_length / 2 : middle_bound = (content_length / 2) + 1;
printf("5\n");
    pthread_t thread1, thread2;
    thread_args args1{content, 0, middle_bound};
    thread_args args2{content, middle_bound, content_length};

    pthread_create(&thread1, NULL, Compressor::compress_t, &args1);
    pthread_create(&thread2, NULL, Compressor::compress_t, &args2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

