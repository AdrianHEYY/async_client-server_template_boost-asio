#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using tcp = boost::asio::ip::tcp;
using std::cout;

extern class Server;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket, Server* serv);
    ~Session();
    void run();
    
    int sizeToTransmit;
    std::string lastMessage;
    void async_write(std::string message);

    void write(std::string& s);

    void wait_for_request();

    void wh(boost::system::error_code ec, size_t len);

private:
    Server* sv;
    boost::asio::streambuf m_buffer;
public:
    tcp::socket m_socket;
};