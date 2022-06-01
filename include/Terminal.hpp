#pragma once
#include "common.hpp"

class Terminal{
    public:
        static inline void err(std::string& text){ printf("[!] %s\n", text.c_str()); }
        static inline void info(std::string& text){ printf("[ ] %s\n", text.c_str()); }
        static inline void success(std::string& text){ printf("[+] %s\n", text.c_str()); }
        static inline void print(void (*print) (std::string&), std::string&& text){ print(text); }
        static inline void print(void (*print) (std::string&), std::string& text){ print(text); }
};