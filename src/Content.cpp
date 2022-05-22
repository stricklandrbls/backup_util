#include "../include/Content.hpp"
#include <string_view>

void ContentBase::setZipFilePath(std::string* data){
    this->zip_path = *data;
    size_t search_index{};

    while(this->zip_path.find(" ") != std::string::npos && this->zip_path.find(" ") > search_index + 1) {
        search_index = this->zip_path.find(" ");
        this->zip_path.replace(this->zip_path.find(" "), 1, "\\ ");
    }
}