#pragma once
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
#include <crow.h>

class Error {
public:
    static crow::response createError(
        std::string errorCode, std::string errorMessage, std::vector<std::string> messageVars, int numericErrorCode, std::string error, int statusCode) {

        crow::response res;

        res.set_header("X-Epic-Error-Name", errorCode);
        res.set_header("X-Epic-Error-Code", std::to_string(numericErrorCode));

        res.code = statusCode;

        nlohmann::json jsonRes = {
            {"errorCode", errorCode},
            {"errorMessage", errorMessage},
            {"messageVars", messageVars},
            {"numericErrorCode", numericErrorCode},
            {"originatingService", "any"},
            {"intent", "prod"},
            {"error_description", errorMessage},
            {"error", error},
        };
        res.body = jsonRes.dump();
        return res;
    }
};