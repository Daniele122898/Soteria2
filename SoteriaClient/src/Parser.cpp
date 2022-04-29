//
// Created by Daniele on 4/29/2022.
//

#include "Parser.h"

Parser::Parser(const std::string& path) {
    if (!Util::File::Exists(path)) {
        ERR("Couldn't find .soteria file.");
        return;
    }

    // TODO: check speed
    // This is pretty inefficient but if it's quick enough then there's no need
    // manually do the line parsing
    auto file = Util::File{path};
    std::string val = std::string{file.Raw()};
    std::istringstream iss{val};
    std::string line;

    auto filepath = std::filesystem::path{path};
    auto parent = filepath.parent_path();

    while (std::getline(iss, line)) {
        if(line.ends_with('\r'))
            line.pop_back();

        if (line.empty() || line[0] == '#' || line[0] == ' ') // ignore comment or whitespace
            continue;

        if (m_id.empty()) {
            m_id = line;
            continue;
        }

        m_paths.emplace_back(parent.string() + "/" + line);
    }
}
