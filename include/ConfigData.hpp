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
        
        std::string&    destination_hostname(){ return this->output_destination.hostname; }
        std::string&    destination_hostpath(){ return this->output_destination.hostpath; }
        std::vector<Content>&  content(){ return this->base_content; }

    private:
        // Containers
        std::vector<Content> base_content;

        // Variable members
        json                    configuration_data;
        OutputDestination       output_destination;
};