//
// Created by brostin on 02.05.22.
//

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

void handler_write(
        const boost::system::error_code& error, // Result of operation.

        std::size_t bytes_transferred           // Number of bytes written from the
        // buffers. If an error occurred,
        // this will be less than the sum
        // of the buffer sizes.
) {
    if (!error) {
        cout << "write callback"<< endl;
    } else {
        std::cerr << "error: " << error.message() << endl;
    }
}

void handler_read(
        const boost::system::error_code& error, // Result of operation.

        std::size_t bytes_transferred           // Number of bytes written from the
        // buffers. If an error occurred,
        // this will be less than the sum
        // of the buffer sizes.
) {
    if (!error) {
        cout << "read callback"<< endl;
    } else {
        std::cerr << "error: " << error.message() << endl;
    }
}

int main() {
    boost::asio::io_service io_service;
//socket creation
    tcp::socket socket(io_service);
//connection
    // socket.async_connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 1234), );
    socket.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 1234 ));
// request/message from client
    const string msg = "Hello from Client!\n";
    boost::system::error_code error;
    socket.wait(boost::asio::ip::tcp::socket::wait_write, error);
    boost::asio::async_write( socket, boost::asio::buffer(msg), handler_write );
    if( !error ) {
        cout << "Client sent hello message!" << endl;
    }
    else {
        cout << "send failed: " << error.message() << endl;
    }
    socket.wait(boost::asio::ip::tcp::socket::wait_read, error);
    // getting response from server
    boost::asio::streambuf receive_buffer;
    boost::asio::async_read(socket, receive_buffer, boost::asio::transfer_all(), handler_read);
    if( error && error != boost::asio::error::eof ) {
        cout << "receive failed: " << error.message() << endl;
    }
    else {
        const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        cout << data << endl;
    }
    return 0;
}
