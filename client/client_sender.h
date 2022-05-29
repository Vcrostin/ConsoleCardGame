//
// Created by brostin on 28.05.22.
//

#pragma once
#include <string>
#include <iostream>
#include <queue>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "../core/utils/string_assist.h"

using namespace boost::asio;
using ip::tcp;
using std::cerr;
using std::cout;
using std::endl;

class ClientSender : public boost::enable_shared_from_this<ClientSender> {
public:
    typedef boost::shared_ptr<ClientSender> pointer;

    static pointer NewClient(boost::asio::io_service& ioService) {
        auto ptr = pointer(new ClientSender(ioService));
        ptr->Connect();
        return ptr;
    }

    void AddMessage(std::string_view sendingData, uint32_t charsPerIter=1024) {
        auto splitStr = string_split(sendingData, charsPerIter);
        for (auto& str : splitStr) {
            q.push(std::string(str));
        }
    }

    void SendAll() {
        cerr << "Starting sending data " << q.size() << " total ..." << endl;
        sendingDataCount = static_cast<int32_t>(q.size());
        if (sendingDataCount > 0) {
            StartupWrite();
        }
        cerr << "Data sent" << endl;
    }

private:
    explicit ClientSender(boost::asio::io_service& ioService) : _ioService(ioService), _socket(ioService) {
    }

    const inline static std::string IP_ADDRESS = "127.0.0.1";

    void Connect() {
        _socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(IP_ADDRESS), 1234));
    }

    void StartupWrite() {
        _socket.wait(boost::asio::ip::tcp::socket::wait_write);
        _socket.write_some(boost::asio::buffer(std::to_string(sendingDataCount)));
        WaitWriteFunction();
    }
    void WaitWriteFunction() {
        _socket.async_wait(
            boost::asio::ip::tcp::socket::wait_write,
            boost::bind(
                &ClientSender::WaitHandler,
                shared_from_this(),
                boost::asio::placeholders::error())
        );
    }
    void WaitHandler (const boost::system::error_code& error) {
        if (!error) {
            WriteFunction();
        }
        else {
            cerr << error.message() << endl;
        }
    }
    void WriteFunction() {
        boost::asio::async_write(
            _socket,
            boost::asio::buffer(q.front()),
            boost::bind(
                &ClientSender::WriteHandler,
                shared_from_this(),
                boost::asio::placeholders::error(),
                boost::asio::placeholders::bytes_transferred()
            )
        );
    }
    void WriteHandler(const boost::system::error_code& error, size_t bytes_transferred) {
        if (!error) {
            q.pop();
            sendingDataCount--;
//            _socket.wait(boost::asio::ip::tcp::socket::wait_read);
//            boost::asio::streambuf receive_buffer;
//            read(_socket, receive_buffer, boost::asio::transfer_all());
            if (sendingDataCount > 0 && !q.empty()) {
                WaitWriteFunction();
            }
        }
        else {
            cerr << error.message() << endl;
        }
    }
    int32_t sendingDataCount = 0;
    enum { max_length = 1024 };
    io_service& _ioService;
    tcp::socket _socket;
    std::queue<std::string> q;
};


