#include "../include/Content.hpp"
#include <string_view>
/**********************************************************************************************************

 *                                           CONTENT BASE CLASS

**********************************************************************************************************/
void ContentBase::setZipFilePath(const std::string& data){
    this->zip_path.string() = data;
    std::string_view zip_v { this->zip_path.string() };
    size_t search_index{};
    if(zip_v.find(" ")){
            while(zip_v.find(" ") != std::string::npos && zip_v.find(" ") > search_index) {
                search_index = zip_v.find(" ");
                this->zip_path.string().replace(zip_v.find(" "), 1, "\\ ");
            }
        }
    

}

bool ContentBase::isValid(const std::string& path){
    std::unique_ptr<std::filesystem::path> path_to_check(new std::filesystem::path{ path });
    if(!std::filesystem::exists(*path_to_check))
        return false;
    return true;
}
/**********************************************************************************************************

 *                                           FILE DERIVED CLASS

**********************************************************************************************************/


/**********************************************************************************************************

 *                                           DIRECTORY DERIVED CLASS

**********************************************************************************************************/

void Directory::pullDirnameFromPath(){
    std::string_view file_path_view = this->file_path.string();
    
    this->dirname = this->file_path.string().substr(file_path_view.find_last_of("/") + 1);
}

void Directory::setParentDirPath(){
    std::string_view path_v = this->file_path.string();

    this->parent_dir_path = path_v.substr(0, path_v.find_last_of("/"));
}