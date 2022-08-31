//
// Created by Daniele on 4/22/2022.
//

#ifndef SOTERIA_APP_H
#define SOTERIA_APP_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Command.h"
#include "BoolOption.h"

namespace ArgParse {

    // Try to get close to https://nullprogram.com/blog/2020/08/01/

    class App {
    public:
        App(std::string name, std::vector<Command> commands, std::string version = "1.0.0", std::string usage = "CLI tool generated using ArgParse") :
            m_name{std::move(name)}, m_commands{std::move(commands)}, m_version{std::move(version)}, m_usage{std::move(usage)} {

            // Add default help option
            std::shared_ptr<IOption> help = std::make_shared<BoolOption>("help");
            m_globalOptions["help"] = help;

            // Create map that references all options for ease of parsing later
            addToOptionsMap(m_commands);
        };

        App(std::string name, std::vector<Command> commands, std::vector<std::shared_ptr<IOption>> options, std::string version = "1.0.0", std::string usage = "CLI tool generated using ArgParse") :
                m_name{std::move(name)}, m_commands{std::move(commands)}, m_version{std::move(version)}, m_usage{std::move(usage)} {

            // Add appwide options
            for (auto& op : options) {
                m_globalOptions[op->GetName()] = op;
                auto& aliases = op->GetAliases();
                for (auto& al : aliases) {
                    m_globalOptions[al] = op;
                }
            }

            // Add default help option
            std::shared_ptr<IOption> help = std::make_shared<BoolOption>("help");
            m_globalOptions["help"] = help;

            // Create map that references all options for ease of parsing later
            addToOptionsMap(m_commands);
        };

        void Run(int argc, char* argv[]);

        void AddCommand(Command command);
        void AddCommands(std::vector<Command>& commands);
        void PrintHelp() const;

        std::unordered_map<std::string_view, std::shared_ptr<IOption>> const& GetGlobalOptions() { return m_globalOptions; }
    private:
        void addToOptionsMap(std::vector<Command>& commands);

        auto findOption(std::string_view view);

        std::string m_name;
        std::vector<ArgParse::Command> m_commands;
        std::unordered_map<std::string_view, std::shared_ptr<IOption>> m_allOptions;

        std::unordered_map<std::string_view, std::shared_ptr<IOption>> m_globalOptions;

        std::string m_version;
        std::string m_usage;
    };

} // ArgParse

#endif //SOTERIA_APP_H
