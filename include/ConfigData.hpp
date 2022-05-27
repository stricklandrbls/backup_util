#pragma once

// System headers
#include <vector>
#include <iostream>

// User defined headers
#include "Content.hpp"
#include "common.hpp"
#include "json.hpp"

// Namespace delclarations
using namespace nlohmann;

struct OutputDestination{
    std::string hostname, hostpath;
};

class ConfigData{
    public:
        ConfigData();
        ~ConfigData(){};

        // void print(Content& cnt){ printf("%s\n", std::get<Directory>(cnt).getPath()); }
        void printAll(){
            for(auto& it : base_content){
                std::cout << it->getPath() << std::endl;
            }
        }
    private:
        // Containers
        // std::vector<Content>    content; Uses variant as practice, but not actually practical
        std::vector<ContentBase*> base_content;

        // Variable members
        json                    configuration_data;
        OutputDestination       output_destination;
};