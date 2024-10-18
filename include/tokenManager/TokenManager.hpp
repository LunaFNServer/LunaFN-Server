#pragma once

#include <regex>
#include <filesystem>
#include <fstream>
#include <chrono>

#include <spdlog/spdlog.h>
#include <fmt/format.h>
#include <jwt-cpp/jwt.h>
#include <jwt-cpp/traits/nlohmann-json/traits.h>
#include <base64.hpp>
#include <nlohmann/json.hpp>

#include "utils/Functions.hpp"

namespace fs = std::filesystem;

class TokenManager {
public:
    typedef struct ClientToken {
        std::string ip;
        std::string token;
    } ClientToken;

    typedef struct AccessToken {
        std::string accountID;
    } AccessToken;

    static TokenManager& get() {
        static TokenManager instance;
        return instance;
    }

    void getTokens();
    std::string createClient(std::string clientID, std::string grantType, std::string ip, int expiresIn);

    std::string jwt_secret = Utils::Functions::MakeID();
    nlohmann::json tokens;

    std::vector<std::string> accessTokens;
    std::vector<std::string> refreshTokens;
    std::vector<std::string> clientTokens;
};