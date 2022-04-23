//
// Created by Daniele on 4/22/2022.
//

#include "App.h"

namespace ArgParse {
    void App::Run(int argc, char **argv) {
        for (auto& com : m_commands) {
            com.Run();
        }

    }
} // ArgParse