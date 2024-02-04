#include "core.h"

#include "Server.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "context.h"

using tcp = boost::asio::ip::tcp;
using std::cout;

namespace server {
	tcp::endpoint ep(boost::asio::ip::address::from_string(""), 80); // privete? ip adress | ! port forwarding !
	Server* server;
	std::thread *thr;
}

namespace server {
	void init() {
		server = new Server(context, ep);
		thr = new std::thread([&]() {
			context.run();
		});
	}
	void close() {
		thr->join();
	}

	void sendMessage(std::string mesage) {
		;
	}
}