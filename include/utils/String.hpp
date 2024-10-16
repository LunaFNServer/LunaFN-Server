#pragma once

#include <vector>
#include <string>
#include <sstream>

namespace Utils {
    class String {
    public:
        static std::vector<std::string> split(std::string s, char del) {
            std::vector<std::string> tokens;
            std::stringstream ss(s);
            std::string token;
            while(std::getline(ss, token, del)) {
                tokens.push_back(token);
            }
            return tokens;
        }
    };
};