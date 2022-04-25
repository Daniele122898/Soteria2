//
// Created by Daniele on 4/25/2022.
//

#include <iostream>
#include <crow.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    std::cout << "Hello from server" << std::endl;

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    app.port(18080).multithreaded().run();
}