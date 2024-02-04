#include <iostream>

#include "core.h"

int main() {
    client::init();
    while (true) {
        std::string str;
        std::cin >> str;
        client::sendMessage(str);
    }

    client::close();
}