#include "Server.h"

#include "Session.h"

Server::Server(boost::asio::io_context& io_context, tcp::endpoint ep)
    : m_acceptor(io_context, ep) {
    do_accept();
}

void Server::do_accept() {
    std::cout << "Listening\n";
    m_acceptor.async_accept([&](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::cout << "conex creeeata pe: "
                << socket.remote_endpoint().address().to_string()
                << ":" << socket.remote_endpoint().port() << '\n';

            std::shared_ptr<Session> b = std::make_shared<Session>(std::move(socket), this);
            b->run();

        }
        else {
            std::cout << "server error: " << ec.message() << std::endl;
        }
        do_accept();
        });
}