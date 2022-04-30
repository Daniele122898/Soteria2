//
// Created by Daniele on 4/29/2022.
//

#include "Parser.h"

Parser::Parser(const std::string& path) {
    if (!Util::File::Exists(path)) {
        ERR("Couldn't find .soteria file.");
        return;
    }

    LOG("Current dir {}", std::filesystem::current_path().string());

    auto file = Util::File{path};
    std::vector<std::string> lines = getLines(file);

    auto filepath = std::filesystem::path{path};
    auto parent = filepath.parent_path();

    for(auto& line : lines) {
        if (line.empty() || line[0] == '#' || line[0] == ' ') // ignore comment or whitespace
            continue;

        if (m_id.empty()) {
            m_id = line;
            continue;
        }

        m_paths.emplace_back(parent.string() + "/" + line);
    }
}

std::vector<std::string> Parser::getLines(Util::File& file) {
    std::vector<std::string> lines;
    std::ostringstream oss;
    for (char c : file.Data()) {
        if (c == '\n') {
            if (oss.tellp() == 0) continue; // dont add empty lines
            lines.emplace_back(oss.str());
            oss.str(std::string{});
            oss.clear();
            continue;
        } else if (c == '\r') { continue; } // skip all \r
        oss << c;
    }
    lines.emplace_back(oss.str());
    return lines;
}
