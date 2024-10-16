#include "crow.h"

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