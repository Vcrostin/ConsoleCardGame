//
// Created by brostin on 02.05.22.
//

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <deque>
#include <iomanip>
#include <memory>
#include "../core/utils/string_assist.h"
#include "../core/configurations/all_configs.h"

using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::cerr;
using std::endl;

class con_handler : public boost::enable_shared_from_this<con_handler> {
private:
    tcp::socket sock;
    boost::asio::io_service::strand m_strand;
    std::string message = "Hello From Server!";
    const int32_t max_length = GLOBAL_GENERAL_CONF_PARSER.GetInt("maxPackageSize");
    std::unique_ptr<char[]> data = std::make_unique<char[]>(max_length);

    explicit con_handler(boost::asio::io_service &io_service) : sock(io_service), m_strand(io_service) {}


public:
    typedef boost::shared_ptr<con_handler> pointer;

    // creating the pointer
    static pointer create(boost::asio::io_service &io_service) {
        return pointer(new con_handler(io_service));
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
            cerr << "New query:" << endl;
            std::string res;
            for (const auto &q: queryData) {
                cerr << q;
                res += q;
            }
            cout << endl << res << endl;

        } else {
            std::cerr << "error: " << err.message() << std::endl;
            sock.close();
        }
    }
};
