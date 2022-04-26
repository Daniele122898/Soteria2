//
// Created by Daniele on 4/22/2022.
//

#include <iostream>
#include <App.h>
#include <Command.h>
#include <vector>
#include "BoolOption.h"
#include "StringOption.h"
#include <fstream>

void Push(ArgParse::Context context) {
    std::cout << "Ran push function " << std::endl;
    for (auto& op: context.options) {
        std::cout << "Option: " << op->GetName() << " with value " << op->GetValue() << std::endl;
    }
    std::cout << " ---------------------------- " << std::endl;

    // open file
    std::ifstream file("F:/Coding/Cpp/Soteria2/test/secrets.txt", std::ios::binary|std::ios::ate);
    // figure out length of file
    std::ifstream::pos_type pos = file.tellg();
    if (pos == 0) {
        std::cout << "File has 0 length" << std::endl;
        return;
    }

    std::vector<char> result(pos);

    file.seekg(0, std::ios::beg);
    file.read(result.data(), pos);

    std::cout << "Contents of read in stuff\n";
    for (char c : result) {
        std::cout << c;
    }

}

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
    }, "0.0.1", "Soteria Client CLI to interface with Server"
    };

    app.Run(argc, argv);

    return 0;
}

