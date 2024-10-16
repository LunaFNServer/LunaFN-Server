#pragma once

class Routes {
public:
    class Auth {
    public:
        static void setupAuthRoutes();
    };

    static void setupAllRoutes() {
        Auth::setupAuthRoutes();
    }
};