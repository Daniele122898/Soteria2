//
// Created by Daniele on 4/22/2022.
//

#ifndef SOTERIA_COMMAND_H
#define SOTERIA_COMMAND_H

#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <unordered_map>
#include "IOption.h"

namespace ArgParse {

    struct Context {
        std::vector<std::shared_ptr<IOption>> const &options;
        std::string_view m_name;
    };

    class Command {
        typedef void(*ActionFunc)(Context);


    public:
        Command(std::string name, ActionFunc action) :
                m_name{std::move(name)}, m_action{action} { setDefaultHelp(); };

        Command(std::string name, ActionFunc action, std::vector<std::string> aliases) :
                m_name{std::move(name)}, m_action{action}, m_aliases{std::move(aliases)} { setDefaultHelp(); };

        Command(std::string name, ActionFunc action, std::vector<std::shared_ptr<IOption>> options) :
                m_name{std::move(name)}, m_action{action}, m_options{std::move(options)} {
            buildOptionMap();
            setDefaultHelp();
        };

        Command(std::string name, ActionFunc action, std::vector<std::shared_ptr<IOption>> options,
                std::vector<std::string> aliases) :
                m_name{std::move(name)}, m_action{action}, m_options{std::move(options)},
                m_aliases{std::move(aliases)} {
            buildOptionMap();
            setDefaultHelp();
        };

        std::vector<std::shared_ptr<IOption>> const &GetOptions() { return m_options; }

        std::string_view GetName() { return m_name; }

        void Run();

        const Command &SetUsage(std::string usage);

        const Command &SetDescription(std::string description);

    private:
        void buildOptionMap();

        void setDefaultHelp();

        void printHelp();

        std::string m_name;
        ActionFunc m_action;
        std::vector<std::shared_ptr<IOption>> m_options;
        std::unordered_map<std::string_view, std::shared_ptr<IOption>> m_optionsMap;

        std::string m_usage;
        std::string m_description;
        std::vector<std::string> m_aliases;
    };

} // ArgParse

#endif //SOTERIA_COMMAND_H
