//
// Created by Daniele on 4/29/2022.
//

#include "init.h"

#include <util.h>
#include <sstream>

void Init(ArgParse::CmdContext context) {
    LOG("Ran init function");
    for (auto& op: context.options) {
        LOG("Option: {} with value {}", op->GetName(), op->GetValue());
    }
    LOG(" ---------------------------- ");
    
    std::string path = "F:/Coding/Cpp/Soteria2/test/data/generated";

    std::stringstream ss;
    ss << "# !! DO NOT REMOVE AND OR ALTER THE FOLLOWING LINES! AUTO-GENERATED !!\n";
    // TODO: REPLACE WITH ID FROM DB
    ss << "12345566\n";
    ss << "# !! WRITE THE FILES TO INCLUDE BELOW !!\n";

    std::string fileContent = ss.str();

    Util::File::Write(path + "/.soteria", fileContent);
}