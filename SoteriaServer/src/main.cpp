//
// Created by Daniele on 4/25/2022.
//

#include <iostream>
#include <crow.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    std::cout << "Hello from server" << std::endl;

    // Has no middleware. Use App<m1,m2> for that.
    crow::SimpleApp app;

#ifndef NDEBUG
    app.loglevel(crow::LogLevel::Debug);
#else
    app.loglevel(crow::LogLevel::Warning);
#endif

    CROW_ROUTE(app, "/push").methods(crow::HTTPMethod::POST)([](const crow::request& req){
//        req.url_params.get("param");
        crow::multipart::message msg(req);
        CROW_LOG_INFO << "body of the first part" << msg.parts[0].body;
        CROW_LOG_INFO << msg.parts[0].headers.find("Content-Disposition")->second.params["filename"];
//        crow::multipart::header header = crow::multipart::get_header_object(msg.parts[0], "Content-Disposition");
        return "thank you";
    });

    app.port(18080).multithreaded().run();
}