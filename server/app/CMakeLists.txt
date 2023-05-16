add_executable(server main.cpp)

# Include ASIO in your project
target_include_directories(server PRIVATE ${asio_SOURCE_DIR}/asio/include)

set(GENERAL_LIBS CLI11::CLI11)

# Link against required libraries
if(WIN32)
    target_link_libraries(server PRIVATE ${GENERAL_LIBS} wsock32 ws2_32)
elseif(UNIX)
    find_package(Threads REQUIRED)
    target_link_libraries(server PRIVATE ${GENERAL_LIBS} Threads::Threads)
endif()