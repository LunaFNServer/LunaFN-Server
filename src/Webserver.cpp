#include "Webserver.hpp"
#include "Routes.hpp"

void Webserver::startWebserver() {
    CROW_ROUTE(this->app, "/")([]() {
        return "Hello world!";
    });

    Routes::setupAllRoutes();
    TokenManager::get().getTokens();

    this->app
        .port(18080)
        .multithreaded()
        .run();
}