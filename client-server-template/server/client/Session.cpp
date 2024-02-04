#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <type_traits>
#include <map>
#include <set>
#include <chrono>

#include "Session.h"

#include "Server.h"

#include "context.h"

Session::Session(tcp::socket socket, Server* serv) :
    m_socket(std::move(socket)), sv(serv) {
    m_socket.set_option(tcp::no_delay(1));
}


Session::~Session() {
    m_socket.close();
}
void Session::run() {
    wait_for_request();
}

void Session::async_write(std::string message) {
    boost::asio::async_write(m_socket, boost::asio::buffer(message.data(), message.length()), std::bind(&Session::wh, this, std::placeholders::_1, std::placeholders::_2));
    sizeToTransmit = message.size() * sizeof(char);
    lastMessage = message;
}

void Session::wh(boost::system::error_code ec, size_t bytes_transferred) {
    if (ec) {
        std::cout << ec.message() << '\n';
    }
    else if (bytes_transferred == lastMessage.length()) {
        // all good
    }
    else {
        boost::asio::async_write(m_socket, boost::asio::buffer(lastMessage.c_str() + bytes_transferred, lastMessage.length() - bytes_transferred), std::bind(&Session::wh, this, std::placeholders::_1, std::placeholders::_2));
    }

    if (!ec) {

    }
    else {
        cout << "Eroare la transmitere: " << ec.message() << '\n';
    }
}

void Session::write(std::string& s) {
    boost::asio::write(m_socket, boost::asio::buffer(s.data(), s.size()));
    return;
}

void Session::wait_for_request() { // read
    auto self(shared_from_this());
    boost::asio::async_read_until(m_socket, m_buffer, "",
        [this, self](boost::system::error_code ec, std::size_t len)
        {
            if (!ec) {
                std::string data{
                    std::istreambuf_iterator<char>(&m_buffer),
                        std::istreambuf_iterator<char>()
                };

                std::cout << " Reading: >" << data << "<\n";

                async_write(data);

                this->wait_for_request();
            }
            else {
                std::cout << "session error: " << ec << std::endl;
                m_socket.close();
                return;
            }
        });
}