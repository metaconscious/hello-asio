#include <asio.hpp>
#include <iostream>

int main()
{
    asio::io_context ioContext{};

    asio::ip::tcp::endpoint remoteEndpoint{ asio::ip::make_address("127.0.0.1"), 12345 };

    asio::ip::tcp::socket socket{ ioContext };

    socket.connect(remoteEndpoint);

    asio::error_code errorCode{};

    std::string message{ "Hello, asio!" };

    socket.write_some(asio::buffer(message), errorCode);

    if (errorCode)
    {
        std::cerr << "Error while writing: " << errorCode.message() << '\n';
        return EXIT_FAILURE;
    }

    char buffer[1024];

    auto bytesReceived{ socket.read_some(asio::buffer(buffer), errorCode) };

    if (errorCode)
    {
        std::cerr << "Error while reading: " << errorCode.message() << '\n';
        return EXIT_FAILURE;
    }

    std::string echo{ buffer, bytesReceived };

    std::cout << "Echo from server: " << echo << '\n';

    return EXIT_SUCCESS;
}