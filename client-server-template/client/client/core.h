#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using tcp = boost::asio::ip::tcp;
using std::cout;

namespace client {
	void init();
	void close();

	void sendMessage(std::string message);
}