//
// Created by Daniele on 4/25/2022.
//

#include <iostream>
#include <crow.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    std::cout << "Hello from server" << std::endl;

    // Has no middleware. Use App<m1,m2> for that.
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]([[maybe_unused]]const crow::request& req){
//        req.url_params.get("param");
        return "Hello world";
    });

    app.port(18080).multithreaded().run();
}