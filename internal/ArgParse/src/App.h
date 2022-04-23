//
// Created by Daniele on 4/22/2022.
//

#ifndef SOTERIA_APP_H
#define SOTERIA_APP_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "Command.h"

namespace ArgParse {

    // Try to get close to https://nullprogram.com/blog/2020/08/01/

    class App {
    public:
        App(std::string name, std::vector<Command> commands) :
            m_name{std::move(name)}, m_commands{std::move(commands)} {
            std::cout << "Created CLI app " << m_name << std::endl;
        };
    private:
        std::string m_name;
        std::vector<ArgParse::Command> m_commands;
    };

} // ArgParse

#endif //SOTERIA_APP_H
