cmake_minimum_required(VERSION 3.26)
project(hello_hello)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS off)

# Include the FetchContent module
include(FetchContent)

# Download ASIO at configure time
FetchContent_Declare(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG asio-1-28-0 # You can specify a specific version/tag/branch here
)

# Populate the content of the ASIO library
FetchContent_MakeAvailable(asio)

FetchContent_Declare(
        cli11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11
        GIT_TAG        v2.3.2
)

FetchContent_MakeAvailable(cli11)

add_subdirectory(server)
add_subdirectory(client)
