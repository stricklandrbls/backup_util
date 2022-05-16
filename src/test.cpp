#include <sys/shm.h>
#include <sys/ipc.h>
#include <filesystem>
#include <stdio.h>
#include "../include/shared-mem.hpp"

int main(){

    SharedMem config_data = {"./config.json"};
    printf("Shared Memory Segments created: %d\n", SharedMemInfo::SHARED_MEM_SEGMENTS);
    printf("Config-data: %s\n", config_data.getShmData());
    
    // key_t   shmkey;
    // std::filesystem::path filepath = {"./config.json"};
    // size_t filesize = std::filesystem::file_size(filepath);

    // shmkey = ftok(filepath.c_str(), 69);

    // int block_id = shmget(shmkey, filesize, 0666|IPC_CREAT);
    // char* buffer = (char*) shmat(block_id, (void*) 0, 0);
    // printf("Buffer<%p>: %s\n", &buffer, buffer);

    // FILE* config_file = fopen(filepath.c_str(), "r");
    // fseek(config_file, 0, 0);
    // fread(buffer, filesize, 1, config_file);
    // fclose(config_file);

    // printf("Buffer<%p>: %s\n",&buffer, buffer);

    // shmctl(block_id, IPC_RMID, (struct shmid_ds*)0);
}