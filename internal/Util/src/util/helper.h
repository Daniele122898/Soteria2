//
// Created by Daniele on 4/27/2022.
//

#ifndef SOTERIA_HELPER_H
#define SOTERIA_HELPER_H

#include <iomanip>
#include <sstream>

namespace Util {
    static std::string GenerateHexString(unsigned char *text, int text_len) {
        std::stringstream ss;
        for (int i = 1; i <= text_len; ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int) text[i - 1] << ' ';
            if (i % 16 == 0)
                ss << '\n';
        }

        return ss.str();
    }
}

#endif //SOTERIA_HELPER_H
