//
// Created by Daniele on 4/22/2022.
//

#include "Command.h"
#include "BoolOption.h"

namespace ArgParse {
    void Command::Run(AppContext ctx) {
        // Check if we have to run the help command instead
        std::shared_ptr<IOption> helpOption = ctx.options.at("help"); // can throw be careful.
        if (helpOption->IsSet()) {
            PrintHelp();
            return;
        }

        m_action(CmdContext{m_options, m_optionsMap, ctx.options, m_name });
    }

    void Command::setDefaultHelp() {
        std::stringstream ss;
        ss << m_name;
        for (auto& op : m_options) {
            ss << " [" << (op->GetName().size() > 1 ? "--" : "-") << op->GetName() << (op->TakesValue() ? " <value>" : "") << "]";
        }
        m_usage = ss.str();
        m_description = "No description";
    }

    const Command &Command::SetUsage(std::string usage) {
        m_usage = std::move(usage);
        return *this;
    }

    const Command &Command::SetDescription(std::string description) {
        m_description = std::move(description);
        return *this;
    }

    void Command::PrintHelp() const {
        std::cout << m_name << "\n";
        std::cout << "  " << m_description << "\n";
        std::cout << "  " << "usage: " << m_usage << std::endl;
    }

    void Command::buildOptionMap() {
        for (auto& op : m_options) {
            m_optionsMap[op->GetName()] = op;
            auto& aliases = op->GetAliases();
            for (auto& al : aliases) {
                m_optionsMap[al] = op;
            }
        }
    }
} // ArgParse