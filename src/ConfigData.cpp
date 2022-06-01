#include "../include/ConfigData.hpp"

using namespace nlohmann;

ConfigData::ConfigData(){
    std::ifstream   input(CONFIG_PATH, std::ifstream::in);

    input >> configuration_data;
    input.close();

    for(const auto& element : configuration_data.items()){
        auto& key = element.key();
        auto& data = element.value();

        if(key == var::DIR){
            printf("dir\n");
            for(const auto& dir : data){
                Directory* entry = new Directory(dir);
                base_content.push_back(entry);
            }
        }
        else if(key == var::FILE){
            Terminal::print(Terminal::err, "File support: Unimplemented!");
        }
        else if(key == var::DEST){
            printf("Dest\n");
            output_destination.hostname = (data)[var::HOST];
            output_destination.hostpath = (data)[var::PATH_D];
        }
    }
    
}