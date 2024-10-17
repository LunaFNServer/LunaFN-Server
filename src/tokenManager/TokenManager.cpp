#include "tokenManager/TokenManager.hpp"

using namespace Utils;

void TokenManager::getTokens() {
    if (!fs::exists(fmt::format("{}/tokens", fs::current_path().string()))) fs::create_directory(fmt::format("{}/tokens", fs::current_path().string()));
    if (!fs::exists(fmt::format("{}/tokens/tokens.json", fs::current_path().string()))) {
        fs::path filePath(fmt::format("{}/tokens/tokens.json", fs::current_path().string()));

        std::ofstream file(filePath);
        if (file.is_open()) {
            nlohmann::json json;

            json["accessTokens"] = nlohmann::json::array();
            json["refeshTokens"] = nlohmann::json::array();
            json["clientTokens"] = nlohmann::json::array();

            file << json.dump();
        }
    }
}

std::string TokenManager::createClient(std::string clientID, std::string grantType, std::string ip, int expiresIn) {
    nlohmann::json payload = {
        {"p", base64::to_base64(Functions::MakeID())},
        {"clsvc", "fortnite"},
        {"t", "s"},
        {"mver", false},
        {"clid", clientID},
        {"ic", true},
        {"am", grantType},
        {"jti", std::regex_replace(Functions::MakeID(), std::regex("-"), "")},
        {"creation_date", std::to_string(std::time(nullptr))},
        {"hours_expire", expiresIn}
    };

    auto token = jwt::create<jwt::traits::nlohmann_json>()
                .set_expires_in(std::chrono::duration<int>(expiresIn))
                .set_payload_claim("payload", payload)
                .sign(jwt::algorithm::hs256{this->jwt_secret});
    
    return token;
}