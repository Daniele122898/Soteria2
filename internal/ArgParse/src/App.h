//
// Created by Daniele on 4/22/2022.
//

#ifndef SOTERIA_APP_H
#define SOTERIA_APP_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Command.h"

namespace ArgParse {

    // Try to get close to https://nullprogram.com/blog/2020/08/01/

    class App {
    public:
        App(std::string name, std::vector<Command> commands) :
            m_name{std::move(name)}, m_commands{std::move(commands)} {
            // Create map that references all options for ease of parsing later
            m_allOptions = {};
            for (auto& com: m_commands) {
                auto& options = com.GetOptions();
                for (auto& op : options) {
                    m_allOptions[op->GetName()] = op;
                }
            }
        };

        void Run(int argc, char* argv[]);
    private:
        std::string m_name;
        std::vector<ArgParse::Command> m_commands;
        std::unordered_map<std::string_view, std::shared_ptr<IOption>> m_allOptions;
    };

} // ArgParse

#endif //SOTERIA_APP_H
