#include "Webserver.hpp"

int main() {
    Webserver* webserver = &Webserver::get();

    webserver->startWebserver();
    
}