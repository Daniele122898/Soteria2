//
// Created by Daniele on 4/22/2022.
//

#include <iostream>
#include <App.h>
#include <Command.h>
#include <vector>
#include "BoolOption.h"
#include "StringOption.h"

void TestFunc(ArgParse::Context context) {
    std::cout << "Ran action function " << context.m_name << std::endl;
    for (auto& op: context.options) {
        std::cout << "Option: " << op->GetName() << " with value " << op->GetValue() << std::endl;
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {

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
            }},
    }, "0.0.1", "Soteria Client CLI to interface with Server"
    };

    std::cout << "------------- Program params --------------" << std::endl;
    for (int i=0; i<argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    std::cout << "-------------------------------------------" << std::endl;

    app.Run(argc, argv);

    return 0;
}

