//
// Created by brostin on 23.06.22.
//

#pragma once

#include <boost/asio.hpp>
#include "client_sender.h"

class Game {
public:
    explicit Game(boost::asio::io_service &ioService) : ioService(ioService), user("Brostin") {

    }

    void Run() {

        auto clientSender = SetupSender(ClientSender::REQUEST_TYPE::CONNECT);
        clientSender->SendAll();

        int32_t gameCode = 1;
        while (gameCode != 0) {
            PrintGameMenu();
            gameCode = ActionGameMenu();
        }

    }

private:

    void PrintGameMenu() const {
        std::cout << "GAME_MENU" << endl;
        // TODO : temporary menu
        std::cout << "Press 0 to exit" << endl;
        std::cout << "Press 1 to check status" << endl;
        std::cout << "Press 2 to get new data" << endl;
        std::cout << "Press 3 to send new data" << endl;
    }

    int32_t ActionGameMenu() {
        int32_t switchNumber;
        std::cin >> switchNumber;
        switch (switchNumber) {
            case 0: {
                break;
            }
            case 1: {
                auto clientSender = SetupSender(ClientSender::REQUEST_TYPE::CHECK_STATUS);
                clientSender->SendAll();
                break;
            }
            case 2: {
                // TODO: add iteration tracker
                auto clientSender = SetupSender(ClientSender::REQUEST_TYPE::GET_UPDATE_DATA);
                clientSender->SendAll();
                break;
            }
            case 3: {
                auto clientSender = SetupSender(ClientSender::REQUEST_TYPE::SEND_DATA);
                clientSender->SendAll();
                break;
            }
            default:
                throw std::invalid_argument("wrong case number");
        }
        return switchNumber;
    }

    ClientSender::pointer SetupSender(ClientSender::REQUEST_TYPE requestType) {
        auto clientSender = ClientSender::NewClient(ioService);
        clientSender->SetUser(user);
        clientSender->AddMessage("info", defaultMsg);
        clientSender->SetRequestType(requestType);
        return clientSender;
    }

    static const string defaultMsg;

    boost::asio::io_service &ioService;
    Core::User user;
};

