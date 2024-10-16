#include <base64.hpp>
#include <spdlog/spdlog.h>

#include "Webserver.hpp"
#include "Routes.hpp"
#include "types/Error.hpp"
#include "utils/String.hpp"

Webserver* webserver = &Webserver::get();

void Routes::Auth::setupAuthRoutes() {
    CROW_ROUTE(webserver->app, "/account/api/oauth/token").methods(crow::HTTPMethod::POST)([](const crow::request& req, crow::response& res) {
        std::vector<std::string> clientIDList;
        std::string clientID;

        try
        {
            clientIDList = Utils::String::split(base64::from_base64(Utils::String::split(req.get_header_value("authorization"), ' ')[1]), ':');

            if (clientIDList.at(1).empty()) throw new std::exception("invalid client id");

            clientID = clientIDList.at(0);
        }
        catch(const std::exception& e)
        {
            spdlog::error("Invalid Client ID Sent");
            res = Error::createError(
                "errors.com.epicgames.common.oauth.invalid_client",
                "It appears that your Authorization header may be invalid or not present, please verify that you are sending the correct headers.",
                {}, 1011, "invalid_client", 400
            );
        }

        res.end();
    });
}