#pragma once

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using tcp = boost::asio::ip::tcp;
using std::cout;

class Server {
public:
    Server(boost::asio::io_context& io_context, tcp::endpoint ep);

    void do_accept();

private:
    tcp::acceptor m_acceptor;

};