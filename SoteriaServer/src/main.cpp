//
// Created by Daniele on 4/25/2022.
//

#include <iostream>
#include <filesystem>
#include <crow.h>
#include <util.h>
#include <nlohmann/json.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    std::cout << "Hello from server" << std::endl;

    // Has no middleware. Use App<m1,m2> for that.
    crow::SimpleApp app;

#ifndef NDEBUG
    app.loglevel(crow::LogLevel::Debug);
#else
    app.loglevel(crow::LogLevel::Warning);
#endif

    CROW_ROUTE(app, "/push").methods(crow::HTTPMethod::POST)([](const crow::request &req) {
//        req.url_params.get("param");
        crow::multipart::message msg(req);
        CROW_LOG_INFO << "body of the first part" << msg.parts[0].body;
        CROW_LOG_INFO << msg.parts[0].headers.find("Content-Disposition")->second.params["filename"];

        for (auto &part: msg.parts) {
            std::string filename = part.headers.find("Content-Disposition")->second.params["filename"];
            Util::File::Write("F:/Coding/Cpp/Soteria2/test/enc/" + filename, part.body);
        }

//        crow::multipart::header header = crow::multipart::get_header_object(msg.parts[0], "Content-Disposition");
        return crow::response{200};
    });

    CROW_ROUTE(app, "/pull").methods(crow::HTTPMethod::GET)([](const crow::request &req) {
        std::string path = "F:/Coding/Cpp/Soteria2/test/enc";
        std::vector<std::string> filenames;
        for (const auto &entry: std::filesystem::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                filenames.emplace_back(entry.path().filename().string());
            }
        }
        nlohmann::json json;
        json["files"] = filenames;
        crow::response resp{200};
        resp.body = json.dump();
        resp.add_header("Content-Type", "application/json");

        return resp;
    });

    app.port(18080).multithreaded().run();
}