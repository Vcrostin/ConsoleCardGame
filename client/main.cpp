//
// Created by brostin on 02.05.22.
//

#include <iostream>
#include <boost/asio.hpp>
#include "menu.h"

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

int main() {
    boost::asio::io_service ioService;
    Menu menu(ioService);
    menu.Start();
    ioService.run();
    return 0;
}
