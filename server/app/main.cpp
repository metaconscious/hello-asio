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
    socket.read_some(asio::buffer(buffer), errorCode);

    if (errorCode)
    {
        std::cerr << "Error while reading: " << errorCode.message() << '\n';
        return EXIT_FAILURE;
    }

    std::cout << std::string_view{ buffer } << '\n';

    return EXIT_SUCCESS;
}
