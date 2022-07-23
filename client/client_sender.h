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
#include "../core/utils/colours_define.h"
#include "../core/utils/json.hpp"
#include "../core/user.h"

using namespace boost::asio;
using ip::tcp;
using std::cerr;
using std::cout;
using std::endl;
using boost::uuids::detail::md5;


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
        cerr << RED << "Starting sending data " << splitStr.size() << " total ..." << RESET << endl;
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

    nlohmann::json GetAll() {
        std::string message = "server, hello!?";
        std::unique_ptr<char[]> data = std::make_unique<char[]>(max_length);
        _socket.read_some(boost::asio::buffer(data.get(), max_length));
        std::deque<std::string> queryData;
        std::string std_dt = data.get();
        auto split_std_dt = string_split(std_dt);
        int32_t num = std::stoi(split_std_dt[0].data());
        int32_t num_of_elem = std::stoi(split_std_dt[1].data());
        // TODO: check hash-sum
        cerr << num << " with num of element " << num_of_elem << " with hash " << split_std_dt[2] << endl;
        _socket.wait(boost::asio::socket_base::wait_write);
        _socket.write_some(boost::asio::buffer(message, max_length));
        for (int i = 0; i < num; ++i) {
            _socket.wait(boost::asio::socket_base::wait_read);
            _socket.read_some(boost::asio::buffer(data.get(), max_length));
            _socket.wait(boost::asio::socket_base::wait_write);
            _socket.write_some(boost::asio::buffer(message, max_length));
            if (i != num - 1) {
                queryData.emplace_back(data.get(), data.get() + max_length);
            } else {
                queryData.emplace_back(data.get(), data.get() + num_of_elem);
            }
        }
        std::string res;
        for (const auto &q: queryData) {
            res += q;
        }
        nlohmann::json json_ret = nlohmann::json::parse(res);
        cerr << endl << json["user"] << endl;
        return json_ret;
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


