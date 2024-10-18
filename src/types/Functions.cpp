#include "utils/Functions.hpp"

std::string Utils::Functions::MakeID() {
    UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
    return uuidGenerator.getUUID().str();
}

std::chrono::time_point<std::chrono::system_clock> Utils::Functions::DateAddHours(std::string pdate, int number) {
    std::tm tm = {};
    strptime(pdate.c_str(), "%a %b %d %Y %H:%M:%S", &tm);
    tm.tm_hour += number;
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}