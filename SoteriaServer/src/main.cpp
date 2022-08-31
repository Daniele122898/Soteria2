//
// Created by Daniele on 4/25/2022.
//

#include <iostream>
#include <filesystem>
#include <crow.h>
#include <util.h>
#include <nlohmann/json.hpp>
#include <SQLiteCpp/SQLiteCpp.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    // Has no middleware. Use App<m1,m2> for that.
    crow::SimpleApp app;

#ifndef NDEBUG
    app.loglevel(crow::LogLevel::Debug);
#else
    app.loglevel(crow::LogLevel::Warning);
#endif

    // setup DB
    std::string dpPath = "./test/data/test.db3";
    SQLite::Database db{dpPath, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE};

    CROW_ROUTE(app, "/push")
    .methods(crow::HTTPMethod::POST)
    ([](const crow::request &req) {
//        req.url_params.get("param");
        crow::multipart::message msg(req);
        CROW_LOG_INFO << msg.parts[0].headers.find("Content-Disposition")->second.params["filename"];

        for (unsigned int i = 0; i < msg.parts.size(); i+=3) {
            auto& filepart = msg.parts[i];
            auto& ivpart = msg.parts[i+1];
            auto& tagpart = msg.parts[i+2];
            std::string filename = filepart.headers.find("Content-Disposition")->second.params["filename"];
            std::string data = std::move(filepart.body);
            data.append(ivpart.body);
            data.append(tagpart.body);

            Util::File::Write("./test/enc/" + filename, data);
        }

//        crow::multipart::header header = crow::multipart::get_header_object(msg.parts[0], "Content-Disposition");
        return crow::response{200};
    });

    CROW_ROUTE(app, "/pull")
    .methods(crow::HTTPMethod::GET)
    ([](const crow::request &req) {
        std::string path = "./test/enc";
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

    CROW_ROUTE(app, "/pull/<string>")
    .methods(crow::HTTPMethod::GET)
    ([](const crow::request &req, std::string filename) {
        std::string directory = "./test/enc";
        std::string path = directory + "/" + filename;
        if (!std::filesystem::exists(path)) {
            return crow::response{404};
        }
        crow::response resp{200};
        Util::File file{path};
        resp.add_header("Content-Type", "application/octet-stream");
        resp.body = file.ToString();

        return resp;
    });

    app.port(18080).multithreaded().run();
}