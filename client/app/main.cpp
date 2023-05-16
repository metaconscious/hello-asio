#include <asio.hpp>
#include <iostream>

int main()
{
    asio::io_context ioContext{};

    asio::ip::tcp::endpoint remoteEndpoint{ asio::ip::make_address("127.0.0.1"), 12345 };

    asio::ip::tcp::socket socket{ ioContext };

    socket.connect(remoteEndpoint);

    char buffer[1024];
    asio::error_code errorCode{};

    socket.read_some(asio::buffer(buffer), errorCode);

    if (errorCode)
    {
        std::cerr << "Error while reading: " << errorCode.message() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}