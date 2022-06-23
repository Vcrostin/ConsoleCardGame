//
// Created by brostin on 23.06.22.
//

#pragma once

#include <boost/asio.hpp>
#include "client_sender.h"

class Game {
public:
    explicit Game(boost::asio::io_service &ioService) : ioService(ioService) {

    }

    void Run() {
        auto clientSender = ClientSender::NewClient(ioService);
        std::string msg = "To be, or not to be, that is the question:\n"
                          "Whether 'tis nobler in the mind to suffer\n"
                          "The slings and arrows of outrageous fortune,\n"
                          "Or to take arms against a sea of troubles\n"
                          "And by opposing end them. To die—to sleep,\n"
                          "No more; and by a sleep to say we end\n"
                          "The heart-ache and the thousand natural shocks\n"
                          "That flesh is heir to: 'tis a consummation\n"
                          "Devoutly to be wish'd. To die, to sleep;\n"
                          "To sleep, perchance to dream—ay, there's the rub:\n"
                          "For in that sleep of death what dreams may come,\n"
                          "When we have shuffled off this mortal coil,\n"
                          "Must give us pause—there's the respect\n"
                          "That makes calamity of so long life.\n"
                          "For who would bear the whips and scorns of time,\n"
                          "Th'oppressor's wrong, the proud man's contumely,\n"
                          "The pangs of dispriz'd love, the law's delay,\n"
                          "The insolence of office, and the spurns\n"
                          "That patient merit of th'unworthy takes,\n"
                          "When he himself might his quietus make\n"
                          "With a bare bodkin? Who would fardels bear,\n"
                          "To grunt and sweat under a weary life,\n"
                          "But that the dread of something after death,\n"
                          "The undiscovere'd country, from whose bourn\n"
                          "No traveller returns, puzzles the will,\n"
                          "And makes us rather bear those ills we have\n"
                          "Than fly to others that we know not of?\n"
                          "Thus conscience doth make cowards of us all,\n"
                          "And thus the native hue of resolution\n"
                          "Is sicklied o'er with the pale cast of thought,\n"
                          "And enterprises of great pith and moment\n"
                          "With this regard their currents turn awry\n"
                          "And lose the name of action.";
        clientSender->AddMessage(msg);
        clientSender->SendAll();
    }

private:
    boost::asio::io_service &ioService;
};

