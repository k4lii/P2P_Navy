#include "Network.hpp"

Network::Network(){

}

Network::~Network(){

}

void Network::Send(std::string message, std::string ip, int port)
{
    io_service io_service;
    ip::tcp::socket client_socket(io_service); // socket creation
    client_socket.connect(tcp::endpoint(address::from_string(ip), port));
    write(client_socket, buffer(message + "\n"));
}

std::string Network::Receive(int port)
{
    io_service io_service;
    tcp::acceptor acceptor_server(io_service, tcp::endpoint(tcp::v4(), port));// Listening for any new incomming connection at port 9999 with IPv4 protocol
    tcp::socket server_socket(io_service);// Creating socket object
    // std::cout << "waiting for connection" << std::endl;
    acceptor_server.accept(server_socket);  // waiting for connection
    streambuf buf;
    read_until(server_socket, buf, "\n");
    std::string data = buffer_cast<const char*>(buf.data());
    data.pop_back();//remove last character(\n)
    return data;
}