#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;

class Network {
public:
    Network();
    bool Start(const std::string &port, bool is_server);
    bool is_connected() const;
    void send_message(const std::string &message);
    std::string receive_message();

private:
    boost::asio::io_context io_context;
    tcp::socket socket;
    tcp::acceptor acceptor;
};

#endif // NETWORK_HPP
