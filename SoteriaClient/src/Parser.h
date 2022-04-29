//
// Created by Daniele on 4/29/2022.
//

#ifndef SOTERIA_PARSER_H
#define SOTERIA_PARSER_H

#include <string>
#include <vector>
#include <util.h>

class Parser {

public:
    explicit Parser(const std::string& path);
private:
    std::vector<std::string> m_paths;
    std::string m_id;

};


#endif //SOTERIA_PARSER_H
