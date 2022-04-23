//
// Created by Daniele on 4/22/2022.
//

#include <iostream>
#include <App.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {

    ArgParse::App app {"My CLI", {}};

    std::cout << "------------- Program params --------------" << std::endl;
    for (int i=0; i<argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    std::cout << "-------------------------------------------" << std::endl;

    return 0;
}