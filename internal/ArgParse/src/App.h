//
// Created by Daniele on 4/22/2022.
//

#ifndef SOTERIA_APP_H
#define SOTERIA_APP_H

#include <string>
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

            // Create vector that references all options for ease of parsing later
            m_allOptions = {};
            for (auto& com: m_commands) {
                auto& options = com.GetOptions();
                m_allOptions.insert(m_allOptions.end(), options.begin(), options.end());
            }
        };

        void Run(int argc, char* argv[]);
    private:
        std::string m_name;
        std::vector<ArgParse::Command> m_commands;
        std::vector<std::shared_ptr<IOption>> m_allOptions;
    };

} // ArgParse

#endif //SOTERIA_APP_H
