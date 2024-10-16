#pragma once

#include <jwt-cpp/jwt.h>

#include <base64.hpp>
#include <nlohmann/json.hpp>

#include "utils/Functions.hpp"

class TokenManager {
public:
    static void createClient(std::string clientID, std::string grantType, std::string ip, int expiresIn);
};