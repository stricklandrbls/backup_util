// #include <sys/shm.h>
// #include <sys/ipc.h>
// #include <filesystem>
// #include <stdio.h>
#include <iostream>
// #include "../include/shared-mem.hpp"
// #include <iostream>
// #include <fstream>

int main(){

    // SharedMem config_data = {"./config.json"};
    // printf("Shared Memory Segments created: %d\n", SharedMemInfo::SHARED_MEM_SEGMENTS);
    // printf("Config-data: %s\n", config_data.getShmData());

    // std::fstream file_stream { "../config.json" };
    // char* buffer{};
    // file_stream.readsome(buffer, 10);
    // printf("%s\n", buffer);

    Logger::print(Logger::LEVEL::SUCCESS, "Test sentence");

    int x = 10;
    int* x_p = &x;
    int& x_r = x;

    std::cout << "x_p: " << x_p << "\nx_r: " << &x_r << std::endl;
}