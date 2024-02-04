#pragma once

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using tcp = boost::asio::ip::tcp;
using std::cout;

class Client {
public:
    Client();
    ~Client();

    int sizeToTransmit;
    std::string lastMessage;
    void async_write(std::string message);

    void write(std::string message);

private:
    tcp::endpoint ep;
    tcp::socket m_socket;
    tcp::resolver m_resolver;
    boost::asio::streambuf m_buffer;

    void wh(boost::system::error_code ec, size_t len);

    void read();

};