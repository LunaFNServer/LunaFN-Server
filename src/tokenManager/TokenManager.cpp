#include "tokenManager/TokenManager.hpp"

using namespace Utils;

void TokenManager::getTokens() {
    fs::path filePath(fmt::format("{}/tokens/tokens.json", fs::current_path().string()));
    if (!fs::exists(fmt::format("{}/tokens", fs::current_path().string()))) fs::create_directory(fmt::format("{}/tokens", fs::current_path().string()));
    if (!fs::exists(filePath)) {
        std::ofstream file(filePath);
        if (file.is_open()) {
            nlohmann::json json;

            json["accessTokens"] = nlohmann::json::array();
            json["refeshTokens"] = nlohmann::json::array();
            json["clientTokens"] = nlohmann::json::array();

            file << json.dump();
        }
        file.close();
    }

    std::ifstream file(filePath);
    if (file.is_open()) {
        nlohmann::json fileJSON = nlohmann::json::parse(file);
        for (auto tokenType : fileJSON) {
            for (auto tokenIndex : tokenType) {
                if (tokenIndex.empty()) continue;
                auto decodedToken = jwt::decode(tokenIndex);
                std::regex_replace(decodedToken.get_token(), std::regex("eg1~"), "");

                if (Utils::Functions::DateAddHours(decodedToken.get_payload_claim("creation_date").as_string(), decodedToken.get_payload_claim("hours_expire").as_integer()) <= std::chrono::system_clock::now()) {
                    tokenType[tokenIndex] = 1;
                }
            }
        }

        std::ofstream outFile(filePath);
        outFile << std::setw(4) << fileJSON << std::endl;
        outFile.close();

        this->accessTokens = fileJSON["accessTokens"].get<std::vector<std::string>>();
        this->refreshTokens = fileJSON["refreshTokens"].get<std::vector<std::string>>();
        this->clientTokens = fileJSON["clientTokens"].get<std::vector<std::string>>();
    }
    file.close();
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
        {"creation_date", std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))},
        {"hours_expire", expiresIn}
    };

    auto token = jwt::create<jwt::traits::nlohmann_json>()
                .set_expires_in(std::chrono::duration<int>(expiresIn))
                .set_payload_claim("payload", payload)
                .sign(jwt::algorithm::hs256{this->jwt_secret});

    this->clientTokens.push_back(token);
    
    return token;
}