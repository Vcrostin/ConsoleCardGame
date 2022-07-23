//
// Created by brostin on 02.05.22.
//

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include <deque>
#include <iomanip>
#include <memory>
#include <utility>
#include "../core/utils/string_assist.h"
#include "../core/configurations/all_configs.h"
#include "../core/session.h"
#include "../core/utils/json.hpp"
#include "../core/user.h"
#include "../core/utils/custom_deque.h"

using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::cerr;
using std::endl;
using boost::uuids::detail::md5;

class con_handler : public boost::enable_shared_from_this<con_handler> {
public:
    typedef boost::shared_ptr<con_handler> pointer;
    typedef std::shared_ptr<CustomDeque<Core::Session>> DequeSessions;
private:
    tcp::socket sock;
    boost::asio::io_service::strand m_strand;
    DequeSessions AllBoards;
    std::string message = "Hello From Server!";
    const uint32_t max_length = GLOBAL_GENERAL_CONF_PARSER.GetInt("maxPackageSize");
    std::unique_ptr<char[]> data = std::make_unique<char[]>(max_length);

    explicit con_handler(boost::asio::io_service &io_service, DequeSessions it) : sock(io_service),
                                                                                  m_strand(io_service),
                                                                                  AllBoards(std::move(it)) {}


public:

    // creating the pointer
    static pointer create(boost::asio::io_service &io_service, DequeSessions it = nullptr) {
        return pointer(new con_handler(io_service, std::move(it)));
    }

//socket creation
    tcp::socket &socket() {
        return sock;
    }

    void start() {
        boost::system::error_code error;
        sock.wait(boost::asio::ip::tcp::socket::wait_read, error);
        sock.async_read_some(
                boost::asio::buffer(data.get(), max_length),
                m_strand.wrap(boost::bind(&con_handler::handle_read,
                                          shared_from_this(),
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred)));

    }

private:
    void handle_read(const boost::system::error_code &err, [[maybe_unused]] size_t bytes_transferred) {
        if (!err) {
            std::deque<std::string> queryData;
            std::string std_dt = data.get();
            auto split_std_dt = string_split(std_dt);
            int32_t num = std::stoi(split_std_dt[0].data());
            int32_t num_of_elem = std::stoi(split_std_dt[1].data());
            // TODO: check hash-sum
            cerr << num << " with num of element " << num_of_elem << " with hash " << split_std_dt[2] << endl;
            sock.wait(boost::asio::socket_base::wait_write);
            sock.write_some(boost::asio::buffer(message, max_length));
            for (int i = 0; i < num; ++i) {
                sock.wait(boost::asio::socket_base::wait_read);
                sock.read_some(boost::asio::buffer(data.get(), max_length));
                sock.wait(boost::asio::socket_base::wait_write);
                sock.write_some(boost::asio::buffer(message, max_length));
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
            nlohmann::json json = nlohmann::json::parse(res);
            RequestHandler(json);
            cerr << endl << json["user"] << endl;
        } else {
            std::cerr << "error: " << err.message() << std::endl;
            sock.close();
        }
    }

    void RequestHandler(nlohmann::json &json) {
        Core::User user(json["user"]);
        switch (json["requestType"].get<int32_t>()) {
            case 1: {
                cerr << "CHECK_STATUS" << endl;
                break;
            }
            case 2: {
                cerr << "GET_UPDATE_DATA" << endl;
                break;
            }
            case 3: {
                cerr << "SEND_DATA" << endl;
                break;
            }
            case 4: {
                cerr << "CONNECT" << endl;
                if (user.GetSessionId() == 0) {
                    ConnectUser(user);
                    user.ToJson(json["user"]);
                    SendBack(json);
                } else {
                    SendBack(json);
                }
                break;
            }
            default:
                throw std::invalid_argument("wrong case number");
        }
    }

    void SendBack(const nlohmann::json &json) {
        string jDump = json.dump();
        auto splitStr = string_split(jDump, max_length);
        md5 hash;
        md5::digest_type digest;
        hash.process_bytes(jDump.data(), jDump.size());
        hash.get_digest(digest);
        string header = (std::to_string(splitStr.size()) + " " +
                         std::to_string(splitStr.back().size()) + " " + toString(digest));
        std::unique_ptr<char[]> data_ptr = std::make_unique<char[]>(max_length);
        cerr << "Starting sending data " << splitStr.size() << " total ..." << endl;
        sock.wait(boost::asio::socket_base::wait_write);
        sock.write_some(boost::asio::buffer(header, max_length));
        sock.wait(boost::asio::socket_base::wait_read);
        sock.read_some(boost::asio::buffer(data_ptr.get(), max_length));
        for (auto spl: splitStr) {
            sock.wait(boost::asio::socket_base::wait_write);
            sock.write_some(boost::asio::buffer(spl.data(), max_length));
            sock.wait(boost::asio::socket_base::wait_read);
            sock.read_some(boost::asio::buffer(data_ptr.get(), max_length));

        }
        cerr << "Data sent" << endl;
    }

    void ConnectUser(Core::User &user) {
        if (AllBoards->Empty() || AllBoards->Back().IsBusy()) {
            AllBoards->AddBack();
        }
        user.SetSessionId(AllBoards->GetLastOneIndexationIdx());
        AllBoards->Back().AddUser(user);
    }
};
