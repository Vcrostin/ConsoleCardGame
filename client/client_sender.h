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
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include "../core/utils/string_assist.h"

using namespace boost::asio;
using ip::tcp;
using std::cerr;
using std::cout;
using std::endl;
using boost::uuids::detail::md5;

inline std::string toString(const md5::digest_type &digest) {
    const auto charDigest = reinterpret_cast<const char *>(&digest);
    std::string result;
    boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(result));
    return result;
}

class ClientSender : public boost::enable_shared_from_this<ClientSender> {
public:
    typedef boost::shared_ptr<ClientSender> pointer;

    static pointer NewClient(boost::asio::io_service& ioService) {
        auto ptr = pointer(new ClientSender(ioService));
        ptr->Connect();
        return ptr;
    }

    void AddMessage(std::string_view sendingData, uint32_t charsPerIter=max_length) {
        auto splitStr = string_split(sendingData, charsPerIter);
        if (splitStr.empty()) {
            //TODO: make custom exception classes
            throw std::invalid_argument("u tried to send an empty string");
        }
        md5 hash;
        md5::digest_type digest;
        hash.process_bytes(sendingData.data(), sendingData.size());
        hash.get_digest(digest);
        q.push((std::to_string(splitStr.size()) + " " + std::to_string(sendingData.size() - charsPerIter * (splitStr.size() - 1)) + " " + toString(digest)));
        for (auto str : splitStr) {
            q.push(std::string(str));
        }
    }

    void SendAll() {
        char data[max_length];
        cerr << "Starting sending data " << q.size() << " total ..." << endl;
        boost::asio::streambuf receive_buffer;
        _socket.wait(boost::asio::socket_base::wait_write);
        _socket.write_some(boost::asio::buffer(q.front(), max_length));
        q.pop();
        _socket.wait(boost::asio::socket_base::wait_read);
        _socket.read_some(boost::asio::buffer(data, max_length));
        size_t num_of_pack = q.size();
        for (size_t i = 0; i < num_of_pack; i++) {
            _socket.wait(boost::asio::socket_base::wait_write);
            _socket.write_some(boost::asio::buffer(q.front(), max_length));
            _socket.wait(boost::asio::socket_base::wait_read);
            _socket.read_some(boost::asio::buffer(data, max_length));
            q.pop();

        }
        cerr << "Data sent" << endl;
    }

private:
    explicit ClientSender(boost::asio::io_service& ioService) : _ioService(ioService), _socket(_ioService) {
    }

    const inline static std::string IP_ADDRESS = "127.0.0.1";

    void Connect() {
        _socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(IP_ADDRESS), 1234));
    }

    enum { max_length = 1000 };
    io_service& _ioService;
    tcp::socket _socket;
    std::queue<std::string> q;
};


