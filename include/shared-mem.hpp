#pragma once
#include <sys/shm.h>
#include <sys/ipc.h>
#include <filesystem>
#include <memory>

using path = std::filesystem::path;

namespace SharedMemInfo{
    static int SHARED_MEM_SEGMENTS = 0;
}

class SharedMem{

    public:
        SharedMem(path filepath): filepath{ filepath }{
            this->shmsize = std::filesystem::file_size(filepath);

            // Create block of shared mem
            shmkey = ftok(filepath.c_str(), ++SharedMemInfo::SHARED_MEM_SEGMENTS);

            if(shm_block_id = shmget(shmkey, this->shmsize, 0666|IPC_CREAT)){
                this->shmdata = (char*) shmat(shm_block_id, (void*)0, 0);

                FILE* config_file = fopen(this->filepath.c_str(), "r");
                fseek(config_file, 0, 0);
                fread(this->shmdata, this->shmsize, 1, config_file);
                fclose(config_file);
                printf("shmdata: %s\n", this->shmdata);
            }
            else{
                printf("Could not get shared memory block");
            }
        };  
        ~SharedMem(){ shmctl(this->shmkey, IPC_RMID, (struct shmid_ds*)0); };
        
        char*   getShmData(){ return (this->shmdata); };

    private:
        key_t   shmkey;
        int     shm_block_id;
        char*   shmdata;
        path    filepath;
        size_t  shmsize;
};