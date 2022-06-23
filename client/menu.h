//
// Created by brostin on 22.06.22.
//

#pragma once

#include <iostream>
#include <iomanip>
#include "../core/utils/colors_define.h"
#include "game.h"
#include <boost/asio.hpp>

using std::cout, std::endl;

class Menu {
public:
    explicit Menu(boost::asio::io_service &ioService) : ioService(ioService) {

    }

    void Start() {
        int i = 0;
        do {
            PrintMenu();
            std::cin >> i;
            system("clear");
            Action(i);
        } while (i != 0);
    }

private:
    boost::asio::io_service &ioService;

    static void PrintMenu() {
        cout << endl << "____MENU____" << endl;
        cout << std::right << std::setw(3) << "0 " << std::left << "Exit" << endl;
        cout << std::right << std::setw(3) << "1 " << std::left << "Start Game" << endl;
        cout << std::right << std::setw(3) << "2 " << std::left << "Collections" << endl;
        cout << std::right << std::setw(3) << "3 " << std::left << "Settings" << endl;
        cout << "____________" << endl;
        cout << "Enter number: ";
    }

    void Action(int i) {
        switch (i) {
            case 0:
                std::cerr << RED << "breaking" << WHITE << std::endl;
                break;
            case 1: {
                std::cerr << RED << "new game..." << WHITE << std::endl;
                Game game(ioService);
                game.Run();
                break;
            }
            case 2:
                std::cerr << RED << "show collections..." << WHITE << std::endl;
                break;
            case 3:
                std::cerr << RED << "settings open" << WHITE << std::endl;
                break;
            default:
                std::cerr << RED << "incorrect action" << WHITE << std::endl;
                break;
        }
    }
};


