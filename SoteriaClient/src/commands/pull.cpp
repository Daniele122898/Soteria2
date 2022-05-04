//
// Created by Daniele on 5/4/2022.
//

#include "pull.h"
#include "cpr/cpr.h"
#include "util.h"

void Pull([[maybe_unused]]ArgParse::CmdContext context) {
    cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:18080/pull"});
    LOG("response {}", r.text);
}