#pragma once

#include <string>
#include <iostream>

namespace server {
	void init();
	void close();

	void sendMessage(std::string mesage);
}