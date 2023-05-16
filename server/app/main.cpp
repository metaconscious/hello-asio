#include <asio.hpp>
#include <cstdlib>
#include <iostream>

int main()
{
    asio::io_context ioContext{};
    asio::ip::tcp::endpoint endpoint{ asio::ip::tcp::v4(), 12345 };
    asio::ip::tcp::acceptor acceptor{ ioContext, endpoint };
    auto socket{ acceptor.accept() };

    char buffer[1024];
    asio::error_code errorCode{};

    while (true)
    {
        auto bytesReceived{ socket.read_some(asio::buffer(buffer), errorCode) };

        if (errorCode == asio::error::eof)
        {
            std::cout << "Socket closed.\n";
            return EXIT_SUCCESS;
        }
        else if (errorCode)
        {
            std::cerr << "Error while reading: " << errorCode.message() << '\n';
            return EXIT_FAILURE;
        }

        std::string_view message{ buffer, bytesReceived };

        if (message == "!exit")
        {
            std::cout << "Close command received from peer.\n";
            return EXIT_SUCCESS;
        }

        std::cout << "Received from client: " << message << '\n';

        socket.write_some(asio::buffer(message), errorCode);

        if (errorCode)
        {
            std::cerr << "Error while writing: " << errorCode.message() << '\n';
            return EXIT_FAILURE;
        }
    }
}
