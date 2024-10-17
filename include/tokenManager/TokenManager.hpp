#pragma once

#include <regex>
#include <filesystem>
#include <fstream>

#include <fmt/format.h>
#include <jwt-cpp/jwt.h>
#include <jwt-cpp/traits/nlohmann-json/traits.h>
#include <base64.hpp>
#include <nlohmann/json.hpp>

#include "utils/Functions.hpp"

namespace fs = std::filesystem;

class TokenManager {
public:
    static TokenManager& get() {
        static TokenManager instance;
        return instance;
    }

    void getTokens();
    std::string createClient(std::string clientID, std::string grantType, std::string ip, int expiresIn);

    std::string jwt_secret = Utils::Functions::MakeID();
    nlohmann::json tokens;
};