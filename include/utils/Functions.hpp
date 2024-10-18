#pragma once

#include <string>
#include <chrono>
#include <sstream>
#include <ctime>

#include <uuid_v4.h>

namespace Utils {
    class Functions {
    public:
        static std::string MakeID();
        static std::chrono::time_point<std::chrono::system_clock> DateAddHours(std::string pdate, int number);
    };
}