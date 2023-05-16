#include <asio.hpp>
#include <iostream>

int main()
{
    asio::io_context ioContext{};

    asio::ip::tcp::endpoint remoteEndpoint{ asio::ip::make_address("127.0.0.1"), 12345 };

    asio::ip::tcp::socket socket{ ioContext };

    socket.connect(remoteEndpoint);

    std::string message{ "Hello, asio!" };
    char buffer[1024];

    while (std::getline(std::cin, message, '\n'))
    {
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        asio::error_code errorCode{};

        socket.write_some(asio::buffer(message), errorCode);

        if (errorCode)
        {
            std::cerr << "Error while writing: " << errorCode.message() << '\n';
            return EXIT_FAILURE;
        }

        auto bytesReceived{ socket.read_some(asio::buffer(buffer), errorCode) };

        if (errorCode == asio::error::eof)
        {
            std::cerr << "Socket closed.\n";
            return EXIT_FAILURE;
        }
        else if (errorCode)
        {
            std::cerr << "Error while reading: " << errorCode.message() << '\n';
            return EXIT_FAILURE;
        }

        std::string echo{ buffer, bytesReceived };

        std::cout << "Echo from server: " << echo << '\n';
    }

    return EXIT_SUCCESS;
}