#include "core.h"

#include "context.h"
#include "client.h"

namespace client {
	boost::asio::ip::tcp::socket so(context);
	boost::asio::ip::tcp::resolver re(context);
	boost::asio::streambuf sb;

    Client* client;

    std::thread *thr;
}

namespace client {
    void as_read() {
        boost::asio::async_read_until(so, sb, "\n", [&](boost::system::error_code ec, size_t len) {
            if (!ec) {
                std::string data{
                    std::istreambuf_iterator<char>(&sb),
                        std::istreambuf_iterator<char>()
                };
                cout << "Reading: " << data << '\n';

                as_read();
            }
            else {
                cout << "Eroare idiotule\n";
            }
            });
    }

	void init() {
        client = new Client();
        thr = new std::thread([&]() {
            context.run();
        });
	}

    void close() {
        thr->join();
    }

    void sendMessage(std::string message) {
        client->async_write(message);
    }
}