//
// Created by Daniele on 4/29/2022.
//

#ifndef SOTERIA_LOG_H
#define SOTERIA_LOG_H

#include <fmt/core.h>
#include <iostream>

#ifndef NDEBUG
#define LOG(...) std::cout << fmt::format(__VA_ARGS__) << std::endl
#else
#define LOG(...)
#endif

#define ERR(...) std::cerr << fmt::format(__VA_ARGS__) << std::endl

#endif //SOTERIA_LOG_H
