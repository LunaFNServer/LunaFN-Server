#include "Webserver.hpp"
#include "Routes.hpp"

void Webserver::startWebserver() {
    CROW_ROUTE(this->app, "/")([]() {
        return "Hello world!";
    });

    Routes::setupAllRoutes();
    try {
        TokenManager::get().getTokens();
    } catch(std::exception& e) {
        spdlog::info("Getting Tokens Exception: {}", e.what());
    }

    this->app
        .port(18080)
        .multithreaded()
        .run();
}