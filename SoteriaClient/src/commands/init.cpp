//
// Created by Daniele on 4/29/2022.
//

#include "commands.h"

#include "util.h"
#include <sstream>
#include <iostream>

void Init(ArgParse::CmdContext context) {
    LOG("Ran init function");
    for (auto& op: context.options) {
        LOG("Option: {} with value {}", op->GetName(), op->GetValue());
    }
    LOG(" ---------------------------- ");
    std::string path = "./test/data/generated";

    // Check if there already exists a .soteria file
    if (Util::File::Exists(path + "/.soteria")) {
        std::cout << ".soteria file already exists! Failed to initialize." << std::endl;
        return;
    }

    std::stringstream ss;
    ss << "# !! DO NOT REMOVE AND OR ALTER THE FOLLOWING LINES! AUTO-GENERATED !!\n";
    // TODO: REPLACE WITH ID FROM DB
    ss << "12345566\n";
    ss << "# !! WRITE THE FILES TO INCLUDE BELOW !!\n";

    std::string fileContent = ss.str();

    Util::File::Write(path + "/.soteria", fileContent);

    std::cout << "Initialized .soteria file and generated new project ID for " << context.optionsMap.at("name")->GetValue() << std::endl;
}