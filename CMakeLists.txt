cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(BackupUtility VERSION 1.0)

message("-- Setting Sources Variable")
set(sources src/main.cpp src/Config.cpp src/Content.cpp)

message("-- Setting Executable: Backup utility")
add_executable(backup-util ${sources})
target_link_libraries(backup-util pthread)

message("-- Setting Executable: test.cpp")
add_executable(test src/test.cpp)

#[[             Add Subdirectories later in the book 
message("------------------ Adding Subdirectories ------------------")
add_subdirectory(src/config)
target_link_libraries(backup-util PRIVATE src/config)
]]