#pragma once
#include "common.hpp"

class Terminal{
    public:
        static inline std::string err(std::string text){
            std::string ret = "[!] ";
            ret += text;
            return ret;
        }
        static inline std::string info(std::string text){
            std::string ret = "[ ] ";
            ret += text;
            return ret;
        }
        static inline std::string success(std::string text){
            std::string ret = "[+] ";
            ret += text;
            return ret;
        }
        static inline void print(std::string (*type) (std::string), std::string text){
            printf("%s\n", type(text).c_str());
        }
};