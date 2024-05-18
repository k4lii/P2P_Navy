#include "Network.hpp"
#include <iostream>

Network::Network() : socket(io_context), acceptor(io_context) {}

bool Network::Start(const std::string &port, bool is_server) {
    try {
        if (is_server) {
            tcp::endpoint endpoint(tcp::v4(), std::stoi(port));
            acceptor.open(endpoint.protocol());
            acceptor.bind(endpoint);
            acceptor.listen();
            std::cout << "Listening on port: " << port << std::endl;
            acceptor.accept(socket);
            std::cout << "Client connected." << std::endl;
        } else {
            tcp::resolver resolver(io_context);
            auto endpoints = resolver.resolve("127.0.0.1", port);
            boost::asio::connect(socket, endpoints);
            std::cout << "Connected to server." << std::endl;
        }
        return true;
    } catch (boost::system::system_error &e) {
        std::cerr << "Boost system error: " << e.what() << std::endl;
        if (is_server) {
            std::cerr << "Server failed to bind to port." << std::endl;
        } else {
            std::cerr << "Client failed to connect to server." << std::endl;
        }
        return false;
    } catch (std::exception &e) {
        std::cerr << "Standard exception: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Unknown error occurred while starting network." << std::endl;
        return false;
    }
}

bool Network::is_connected() const {
    return socket.is_open();
}

void Network::send_message(const std::string &message) {
    if (is_connected()) {
        boost::asio::write(socket, boost::asio::buffer(message + "\n"));
    } else {
        std::cerr << "No connection available to send message" << std::endl;
    }
}

std::string Network::receive_message() {
    if (is_connected()) {
        boost::asio::streambuf buf;
        boost::asio::read_until(socket, buf, "\n");
        std::istream input(&buf);
        std::string message;
        std::getline(input, message);
        return message;
    } else {
        std::cerr << "No connection available to receive message" << std::endl;
        return "";
    }
}
