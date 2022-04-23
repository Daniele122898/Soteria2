//
// Created by Daniele on 4/22/2022.
//

#ifndef SOTERIA_COMMAND_H
#define SOTERIA_COMMAND_H

#include <string>
#include <utility>
#include <iostream>

namespace ArgParse {

    class Command {
        typedef void(*ActionFunc)();

    public:
        explicit Command(std::string name, ActionFunc action): m_action{action}, m_name{std::move(name)} {};

        void Run();
    private:
        ActionFunc m_action;
        std::string m_name;
    };

} // ArgParse

#endif //SOTERIA_COMMAND_H
