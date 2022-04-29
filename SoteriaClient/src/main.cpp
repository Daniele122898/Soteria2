//
// Created by Daniele on 4/22/2022.
//

#include <iostream>
#include <App.h>
#include <Command.h>
#include <vector>
#include <util/log.h>

#include "BoolOption.h"
#include "StringOption.h"
#include "push.h"
#include "init.h"
#include "Parser.h"

void TestFunc(ArgParse::CmdContext context) {
    LOG("Ran action function {}", context.m_name);
    for (auto& op: context.options) {
        LOG("Option: {} with value {}", op->GetName(), op->GetValue());
    }
}

int main(int argc, char* argv[]) {

    ArgParse::App app {"My CLI", std::vector{
        ArgParse::Command{
            "test",
            TestFunc,
            {
                    std::make_shared<ArgParse::BoolOption>("a"),
                    std::make_shared<ArgParse::BoolOption>("b"),
                    std::make_shared<ArgParse::StringOption>("c"),
                    std::make_shared<ArgParse::BoolOption>("long-option"),
                    std::make_shared<ArgParse::StringOption>("output", true),
            }}.SetDescription("Test command to test argparse"),
        ArgParse::Command{
            "pull",
            TestFunc,
            {
                std::make_shared<ArgParse::StringOption>("file", false, std::vector<std::string>{"f"})
            }
            }.SetDescription("Pull files from the Soteria server."),
        ArgParse::Command{
                "push",
                Push,
                {
                        std::make_shared<ArgParse::StringOption>("file", false, std::vector<std::string>{"f"})
                }
        }.SetDescription("Push files from the Soteria server."),
        ArgParse::Command{
                "setup",
                TestFunc,
        }.SetDescription("Command to setup soteria client"),
        ArgParse::Command{
            "init",
            Init,
        }.SetDescription("Command to initialize soteria folder. This will generate a new project on the server and assign a new uuid.")
    }, "0.0.1", "Soteria Client CLI to interface with Server"
    };
    
    Parser p{"F:/Coding/Cpp/Soteria2/test/data/.soteria"};

    app.Run(argc, argv);

    return 0;
}

