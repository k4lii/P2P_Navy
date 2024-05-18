#include "Network.hpp"
#include <iostream>

Network::Network() : socket(io_context), acceptor(nullptr) {}

bool Network::Start(const std::string &port, bool is_server, const std::string &ip) {
    try {
        if (is_server) {
            // Initialize acceptor only for server
            acceptor.reset(new tcp::acceptor(io_context, tcp::endpoint(tcp::v4(), std::stoi(port))));
            acceptor->listen();
            std::cout << "Server listening on port: " << port << std::endl;
            acceptor->accept(socket);
            std::cout << "Client connected." << std::endl;
        } else {
            tcp::resolver resolver(io_context);
            auto endpoints = resolver.resolve(ip, port);
            boost::asio::connect(socket, endpoints);
            std::cout << "Connected to server at " << ip << ":" << port << std::endl;
        }
        return true;
    } catch (boost::system::system_error &e) {
        std::cerr << "Network error: " << e.what() << " in " << (is_server ? "server" : "client") << " mode." << std::endl;
        return false;
    }
}

bool Network::is_connected() const {
    return socket.is_open();
}

void Network::send_message(const std::string &message) {
    if (is_connected()) {
        boost::asio::write(socket, boost::asio::buffer(message + "\n")); // Ensure each message ends with a newline for proper parsing.
    } else {
        std::cerr << "No connection available to send message" << std::endl;
    }
}

std::string Network::receive_message() {
    if (is_connected()) {
        boost::asio::streambuf buf;
        boost::asio::read_until(socket, buf, "\n"); // Read until newline character.
        std::istream input(&buf);
        std::string message;
        std::getline(input, message);
        return message;
    } else {
        std::cerr << "No connection available to receive message" << std::endl;
        return "error"; // Returning explicit "error" can help identify issues.
    }
}
