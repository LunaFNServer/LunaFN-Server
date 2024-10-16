cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(LunaServer VERSION 1.0.0)

file (GLOB_RECURSE SOURCES
    src/*.cpp
    include/*.hpp
)

include_directories(include/)

add_executable(${PROJECT_NAME} ${SOURCES})

include(cmake/CPM.cmake)

CPMAddPackage("gh:fmtlib/fmt#10.2.1")
CPMAddPackage("gh:gabime/spdlog@1.14.1")
CPMAddPackage("gh:tobiaslocker/base64#387b32f")
CPMAddPackage("gh:nlohmann/json#6325839")
target_link_libraries(${PROJECT_NAME} PUBLIC fmt spdlog nlohmann_json)
include_directories(${base64_SOURCE_DIR}/include/)

FetchContent_Declare(curl
    URL https://curl.se/download/curl-8.5.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP true
    OVERRIDE_FIND_PACKAGE # this one
)
FetchContent_MakeAvailable(curl)
find_package(Threads REQUIRED)
find_package(curl)
if(CURL_FOUND)
    message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
    message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
    message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")
else()
    message(STATUS "didnt find curl :(((((")
endif()

FetchContent_Declare(OpenSSL
    URL https://github.com/openssl/openssl/releases/download/openssl-3.3.2/openssl-3.3.2.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP true
    OVERRIDE_FIND_PACKAGE # this one
)
FetchContent_MakeAvailable(OpenSSL)

include(FetchContent)
FetchContent_Declare(asio
  GIT_REPOSITORY  https://github.com/chriskohlhoff/asio.git
  GIT_TAG         asio-1-29-0
  GIT_SHALLOW     TRUE
)
FetchContent_MakeAvailable(asio)

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
# Use as standalone library and do not allow deprecated features
target_compile_definitions(asio INTERFACE ASIO_STANDALONE)
# Link threads as dependency
target_link_libraries(asio INTERFACE Threads::Threads)

set(ASIO_INCLUDE_DIR "${asio_SOURCE_DIR}/asio/include")

CPMAddPackage("gh:CrowCpp/Crow#v1.2.0")
CPMAddPackage("gh:Thalhammer/jwt-cpp#83703d7")

include_directories("${asio_SOURCE_DIR}/asio/include" "${Crow_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} INTERFACE CURL::libcurl CURL::curl asio Crow::Crow jwt-cpp)