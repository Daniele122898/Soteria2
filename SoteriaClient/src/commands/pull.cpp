//
// Created by Daniele on 5/4/2022.
//

#include "pull.h"
#include "cpr/cpr.h"
#include "util.h"
#include "../enc.h"
#include <nlohmann/json.hpp>

void Pull([[maybe_unused]]ArgParse::CmdContext context) {
    cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:18080/pull"});
    LOG("response {}", r.text);
    auto j = nlohmann::json::parse(r.text);
    std::vector<std::pair<cpr::AsyncResponse, std::string>> resps;
    for (auto& val : j["files"]) {
        std::string filename = val.get<std::string>();
        resps.emplace_back(
                cpr::GetAsync(cpr::Url{"http://127.0.0.1:18080/pull/" + filename }),
                filename
                );
    }

    /* A 256 bit key */
    unsigned char key[32];
    std::string pw = "testpassword1231231";
    sha256(reinterpret_cast<unsigned char *>(pw.data()), static_cast<int>(pw.size()), key);

    for (auto& [resp, filename] : resps) {
        cpr::Response rr = resp.get();
        unsigned char decryptedtext[rr.text.size()];
        std::string ivstr = rr.text.substr(rr.text.size()-28, 12);
        std::string tag = rr.text.substr(rr.text.size() - 16);
        int decryptedLen = gcm_decrypt(
                reinterpret_cast<unsigned char *>(rr.text.data()),
                static_cast<int>(rr.text.size()-28),
                nullptr, 0,
                reinterpret_cast<unsigned char*>(tag.data()),
                key,
                reinterpret_cast<unsigned char*>(ivstr.data()), 12,
                decryptedtext);

        Util::File::Write(
                "F:/Coding/Cpp/Soteria2/test/dec/"+filename,
                reinterpret_cast<char*>(decryptedtext), decryptedLen);
    }

}