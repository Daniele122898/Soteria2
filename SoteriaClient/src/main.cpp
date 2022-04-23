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
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {

    ArgParse::App app {"My CLI", std::vector{
        ArgParse::Command{
            "Test",
            TestFunc,
            {
                    std::make_shared<ArgParse::BoolOption>(ArgParse::BoolOption {"flag1", false}),
                    std::make_shared<ArgParse::BoolOption>(ArgParse::BoolOption {"flag2", false}),
                    std::make_shared<ArgParse::BoolOption>(ArgParse::BoolOption {"long-option", false}),
                    std::make_shared<ArgParse::StringOption>(ArgParse::StringOption {"output", true}),
            }}
    }};

    std::cout << "------------- Program params --------------" << std::endl;
    for (int i=0; i<argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    std::cout << "-------------------------------------------" << std::endl;

    app.Run(argc, argv);

    return 0;
}

