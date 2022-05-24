#include "../include/Content.hpp"
#include <string_view>
/**********************************************************************************************************

 *                                           CONTENT BASE CLASS

**********************************************************************************************************/
void ContentBase::setZipFilePath(std::string* data){
    this->zip_path = *data;
    std::string_view zip_v { this->zip_path.string() };
    size_t search_index{};

    while(zip_v.find(" ") != std::string::npos && zip_v.find(" ") > search_index + 1) {
        search_index = zip_v.find(" ");
        this->zip_path.string().replace(zip_v.find(" "), 1, "\\ ");
    }
}

/**********************************************************************************************************

 *                                           FILE DERIVED CLASS

**********************************************************************************************************/

File::File(std::string path);