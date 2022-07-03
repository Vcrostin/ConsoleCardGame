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
#include "../core/configurations/all_configs.h"
#include "../core/utils/json.hpp"
#include "../core/user.h"

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

    enum struct REQUEST_TYPE {
        DEFAULT = 0,
        CHECK_STATUS = 1,
        GET_UPDATE_DATA = 2,
        SEND_DATA = 3,
        CONNECT = 4,
    };

    static pointer NewClient(boost::asio::io_service &ioService) {
        auto ptr = pointer(new ClientSender(ioService));
        ptr->Connect();
        return ptr;
    }

    void AddMessage(std::string_view key, std::string_view sendingData) {
        if (sendingData.empty()) {
            //TODO: make custom exception classes
            throw std::invalid_argument("u tried to send an empty string");
        }
        json[std::string(key)] = sendingData;
    }

    void SetUser(const Core::User &user) {
        user.ToJson(json["user"]);
    }

    void SetRequestType(const REQUEST_TYPE &requestType) {
        json["requestType"] = static_cast<int>(requestType);
    }

    void SendAll() {
        string jDump = json.dump();
        auto splitStr = string_split(jDump, max_length);
        md5 hash;
        md5::digest_type digest;
        hash.process_bytes(jDump.data(), jDump.size());
        hash.get_digest(digest);
        string header = (std::to_string(splitStr.size()) + " " +
                         std::to_string(splitStr.back().size()) + " " + toString(digest));
        std::unique_ptr<char[]> data = std::make_unique<char[]>(max_length);
        cerr << "Starting sending data " << splitStr.size() << " total ..." << endl;
        _socket.wait(boost::asio::socket_base::wait_write);
        _socket.write_some(boost::asio::buffer(header, max_length));
        _socket.wait(boost::asio::socket_base::wait_read);
        _socket.read_some(boost::asio::buffer(data.get(), max_length));
        for (auto spl: splitStr) {
            _socket.wait(boost::asio::socket_base::wait_write);
            _socket.write_some(boost::asio::buffer(spl.data(), max_length));
            _socket.wait(boost::asio::socket_base::wait_read);
            _socket.read_some(boost::asio::buffer(data.get(), max_length));

        }
        cerr << "Data sent" << endl;
    }

private:
    explicit ClientSender(boost::asio::io_service &ioService) : _ioService(ioService), _socket(_ioService) {
    }

    const std::string IP_ADDRESS = GLOBAL_GENERAL_CONF_PARSER.GetString("ipAddress");

    void Connect() {
        _socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(IP_ADDRESS), portNumber));
    }

    const uint32_t max_length = GLOBAL_GENERAL_CONF_PARSER.GetInt("maxPackageSize");

    const uint32_t portNumber = GLOBAL_GENERAL_CONF_PARSER.GetInt("portNumber");

    io_service &_ioService;
    tcp::socket _socket;
    nlohmann::json json;
};


