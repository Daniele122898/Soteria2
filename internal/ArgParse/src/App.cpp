//
// Created by Daniele on 4/22/2022.
//

#include "App.h"
#include <fmt/core.h>
#include <iostream>

namespace ArgParse {
    auto App::findOption(std::string_view view) {

        if (auto ia = m_allOptions.find(view); ia != m_allOptions.end()) {
            return ia;
        } else if (auto ig = m_globalOptions.find(view); ig != m_globalOptions.end()) {
            return ig;
        }

        return m_allOptions.end();
    }

    // TODO: rewrite this entire thing
    void App::Run(int argc, char **argv) {
        // Skip first one since its program name
        try {
            std::vector<std::string> commands{};
            for (int i = 1; i < argc; ++i) {
                auto arg = argv[i];
                if (arg[0] != '-') {
                    // TODO: Fix this mess
                    if (std::string(arg) == "help") {
                        PrintHelp();
                        return;
                    }
                    commands.emplace_back(arg);
                    continue;
                }

                auto addConsume = [&i, &argv, argc](const std::shared_ptr<IOption> &op) {
                    if (i + 1 >= argc || argv[i + 1][0] == '-') {
                        throw std::invalid_argument(
                                fmt::format("Flag '{}' consumes a value but there is none to consume", op->GetName()));
                    }
                    // Otherwise next up is some string we can consume
                    op->Set(std::string{argv[++i]});
                };

                if (arg[1] != '-') {
                    // We're dealing with a short option
                    int j = 1;
                    while (arg[j] != '\0') {
                        if (auto f = findOption(std::string_view{&arg[j], 1}); f != m_allOptions.end()) {
                            auto &op = f->second;
                            // check if it doesnt consumes anything
                            if (!op->TakesValue()) {
                                // Doesnt consume so we can just set it and be done since its most likely a boolean flag
                                op->Set();
                                ++j;
                                continue;
                            }
                            // Flag consumes value
                            // if its an assimilation of 1 char flags it has to be the last one otherwise we have to throw
                            if (arg[j + 1] != '\0') {
                                throw std::invalid_argument(
                                        fmt::format("Flag '{}' consumes a value but is not the last option", arg[j]));
                            }
                            addConsume(op);
                            break;

                        } else {
                            // Couldn't find option so we should probably fail here
                            throw std::invalid_argument(fmt::format("Invalid Flag: {}", arg[j]));
                        }
                    }
                } else {
                    std::string_view view{&arg[2]};
                    if (auto f = findOption(view); f != m_allOptions.end()) {
                        auto &op = f->second;
                        // check if it doesnt consumes anything
                        if (!op->TakesValue()) {
                            // Doesnt consume so we can just set it and be done since its most likely a boolean flag
                            op->Set();
                            continue;
                        }
                        addConsume(op);
                    } else {
                        // Couldn't find option so we should probably fail here
                        throw std::invalid_argument(fmt::format("Invalid Flag: {}", view));
                    }
                }
            }

            if (commands.empty()) {
                std::cout << "No commands have been passed to commandline. \n" << std::endl;
                PrintHelp();
                throw std::invalid_argument("No commands have been passed to commandline.");
            }

            // TODO: Add support for subcommands
            for (auto &com: m_commands) {
                if (com.GetName() == commands[0]) {
                    for (auto &op: com.GetOptions()) {
                        if (op->IsRequired() && !op->IsSet()) {
                            throw std::invalid_argument(
                                    fmt::format("Option {} is required but was not set", op->GetName()));
                        }
                    }
                    com.Run({m_globalOptions});
                    return;
                }
            }

            std::cout << "Command not found. \n" << std::endl;
            PrintHelp();
            throw std::invalid_argument("Command not found");
        } catch (std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
            return;
        }
    }

    void App::AddCommand(Command command) {
        m_commands.emplace_back(command);

        // TODO: There must be a less moronic way of doing this.
        std::vector<Command> com = {command};
        addToOptionsMap(com);
    }

    void App::AddCommands(std::vector<Command> &commands) {
        m_commands.insert(m_commands.end(), commands.begin(), commands.end());

        addToOptionsMap(commands);
    }

    void App::addToOptionsMap(std::vector<Command> &commands) {
        // TODO: potentially check for duplicates -> Happens quickly with single char shortcuts.
        for (auto &com: commands) {
            auto &options = com.GetOptions();
            for (auto &op: options) {
                m_allOptions[op->GetName()] = op;
                auto &aliases = op->GetAliases();
                for (auto &al: aliases) {
                    m_allOptions[al] = op;
                }
            }
        }
    }

    void App::PrintHelp() const {
        std::cout << m_name << " - " << m_version << "\n";
        std::cout << m_usage << "\n\n";
        std::cout << "Available commands:" << std::endl;
        
        for (auto& com : m_commands) {
            com.PrintHelp();
            std::cout << "\n";
        }
    }
} // ArgParse