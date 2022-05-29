//
// Created by brostin on 02.05.22.
//

#include <iostream>
#include <boost/asio.hpp>
#include "client_sender.h"

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

int main() {
    boost::asio::io_service ioService;
    std::string msg = "Client sent hello message";
    ClientSender::pointer clientSender = ClientSender::NewClient(ioService);
    clientSender->AddMessage(msg);
    clientSender->SendAll();

//    boost::asio::streambuf receive_buffer;
//    boost::asio::async_read(socket, receive_buffer, boost::asio::transfer_all(), handler_read);
//    if( error && error != boost::asio::error::eof ) {
//        cout << "receive failed: " << error.message() << endl;
//    }
//    else {
//        const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
//        cout << data << endl;
//    }
    return 0;
}
