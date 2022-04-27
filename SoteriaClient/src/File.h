//
// Created by Daniele on 4/27/2022.
//

#ifndef SOTERIA_FILE_H
#define SOTERIA_FILE_H

#include <vector>
#include <fstream>
#include <iostream>

class File {
public:
    explicit File(std::string const& path) {
        // open file
        std::ifstream file(path, std::ios::binary|std::ios::ate|std::ios::in);
        // figure out length of file
        std::ifstream::pos_type pos = file.tellg();
        if (pos == 0) {
            std::cerr << "File [" << path << "] has 0 length (probably doesnt exist)" << std::endl;
            return;
        }

        m_size = pos;

        m_data = std::vector<char>(pos);

        file.seekg(0, std::ios::beg);
        file.read(m_data.data(), pos);
        file.close();
    }

    std::vector<char>& Data() {return m_data;}
    char* Raw() { return m_data.data(); }
    [[nodiscard]] size_t Size() const { return m_size; }

    static void Write(std::string const& path, char* data, int data_len) {
        std::ofstream fout;
        fout.open(path, std::ios::binary|std::ios::out);
        if (!fout.is_open()) {
            std::cerr << "Couldnt open file: " << path << std::endl;
            return;
        }
        fout.write(data, data_len);
        fout.close();
    }

    static void Write(std::string const& path, std::string&& str) {
        Write(path, str.data(), static_cast<int>(str.size()));
    }

    static void Write(std::string const& path, std::string& str) {
        Write(path, str.data(), static_cast<int>(str.size()));
    }

    static void Write(std::string const& path, unsigned char* data, int data_len) {
        Write(path, reinterpret_cast<char*>(data), data_len);
    }

private:
    std::vector<char> m_data;
    size_t m_size;
};


#endif //SOTERIA_FILE_H
