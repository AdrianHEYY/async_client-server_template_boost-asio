#include "client.h"

#include "context.h"

Client::Client()
    : m_socket(context), m_resolver(context)
{
    tcp::endpoint ep = boost::asio::connect(m_socket, m_resolver.resolve("", "80")); // public ip adress and a port
    read();
}

Client::~Client() {
    boost::system::error_code ec;
    m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    m_socket.close();
}

void Client::async_write(std::string message) {
    boost::asio::async_write(m_socket, boost::asio::buffer(message.data(), message.length()), std::bind(&Client::wh, this, std::placeholders::_1, std::placeholders::_2));
    sizeToTransmit = message.size() * sizeof(char);
    lastMessage = message;
}

void Client::write(std::string message) {
    boost::asio::write(m_socket, boost::asio::buffer(message.data(), message.length()));
}

void Client::wh(boost::system::error_code ec, size_t bytes_transferred) {
    if (ec) {
        std::cout << ec.message() << '\n';
    }
    else if (bytes_transferred == lastMessage.length()) {
        // all good
    }
    else {
        boost::asio::async_write(m_socket, boost::asio::buffer(lastMessage.c_str() + bytes_transferred, lastMessage.length() - bytes_transferred), std::bind(&Client::wh, this, std::placeholders::_1, std::placeholders::_2));
    }
    
    if (!ec) {
        
    }
    else {
        cout << "Eroare la transmitere: " << ec.message() << '\n';
    }
}

void Client::read() { // read

    boost::asio::async_read_until(m_socket, m_buffer, "",
        [this](boost::system::error_code ec, std::size_t len)
        {
            if (!ec) {
                std::string data{
                    std::istreambuf_iterator<char>(&m_buffer),
                        std::istreambuf_iterator<char>()
                };

                std::cout << "Reading: " << data << '\n';

                this->read();
            }
            else {
                std::cout << "error: " << ec << std::endl;;
            }
        }); 
}