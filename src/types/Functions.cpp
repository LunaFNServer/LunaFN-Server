#include "utils/Functions.hpp"

std::string Utils::Functions::MakeID() {
    UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
    return uuidGenerator.getUUID().str();
}