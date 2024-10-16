#include "Webserver.hpp"

void Webserver::startWebserver() {
    CROW_ROUTE(this->app, "/")([]() {
        return "Hello world!";
    });

    this->app
        .port(18080)
        .multithreaded()
        .run();
}