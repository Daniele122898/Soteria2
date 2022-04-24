//
// Created by Daniele on 4/22/2022.
//

#include "Command.h"
#include "BoolOption.h"

namespace ArgParse {
    void Command::Run() {
        m_action(Context{ m_options, m_name });
    }

    void Command::setDefaultHelp() {
        m_options.emplace_back(BoolOption{"help"});

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
} // ArgParse