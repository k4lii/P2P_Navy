#pragma once
#include <boost/asio.hpp>
#include <memory>

using boost::asio::ip::tcp;

class Network {
public:
    Network();
    bool Start(const std::string& port, bool is_server, const std::string& ip);
    bool is_connected() const;
    void send_message(const std::string& message);
    std::string receive_message();

private:
    boost::asio::io_context io_context;
    tcp::socket socket;
    std::unique_ptr<tcp::acceptor> acceptor;
};
