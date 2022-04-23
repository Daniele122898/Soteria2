//
// Created by Daniele on 4/22/2022.
//

#include "Command.h"

namespace ArgParse {
    void Command::Run() {
        std::cout << "Ran command " << m_name << std::endl;
    }
} // ArgParse