//
// Created by Daniele on 4/29/2022.
//

#ifndef SOTERIA_PARSER_H
#define SOTERIA_PARSER_H

#include <string>
#include <sstream>
#include <vector>
#include <util.h>

class Parser {

public:
    explicit Parser(const std::string& path);

    std::string_view GetId() {return m_id;}
    std::vector<std::filesystem::path> const& GetPaths() {return m_paths;}
private:
    static std::vector<std::string> getLines(Util::File& file);

    std::vector<std::filesystem::path> m_paths;
    std::string m_id;

};


#endif //SOTERIA_PARSER_H
