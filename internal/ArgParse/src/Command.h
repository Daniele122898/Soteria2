//
// Created by Daniele on 4/22/2022.
//

#ifndef SOTERIA_COMMAND_H
#define SOTERIA_COMMAND_H

#include <string>
#include <iostream>
#include <vector>
#include "IOption.h"

namespace ArgParse {

    struct Context {
        std::vector<std::shared_ptr<IOption>> const& options;
        std::string_view m_name;
    };

    class Command {
        typedef void(*ActionFunc)(Context);


    public:
        explicit Command(std::string name, ActionFunc action) :
            m_action{action}, m_name{std::move(name)} {};
        explicit Command(std::string name, ActionFunc action, std::vector<std::shared_ptr<IOption>> options) :
            m_action{action}, m_name{std::move(name)}, m_options{std::move(options)} {};

        std::vector<std::shared_ptr<IOption>> const& GetOptions() { return m_options;}
        std::string_view GetName() { return m_name; }

        void Run();
    private:
        ActionFunc m_action;
        std::vector<std::shared_ptr<IOption>> m_options;
        std::string m_name;
    };

} // ArgParse

#endif //SOTERIA_COMMAND_H
