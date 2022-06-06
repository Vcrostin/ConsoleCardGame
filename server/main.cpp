//
// Created by brostin on 02.05.22.
//

#include <iostream>
#include <boost/asio.hpp>
#include "server.h"

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    try {
        boost::asio::io_service io_service;
        Server server(io_service);
        io_service.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << endl;
    }
    return 0;
}