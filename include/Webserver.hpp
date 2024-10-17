#pragma once
#include <string>

#include "crow.h"
#include "tokenManager/TokenManager.hpp"

class Webserver {
public:
    static Webserver& get() {
        static Webserver instance;
        return instance;
    }

    void startWebserver();

    // variables
    crow::SimpleApp app;
};