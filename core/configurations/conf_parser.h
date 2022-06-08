//
// Created by brostin on 05.06.22.
//

#pragma once

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include "../utils/path_manip.h"

using std::string;
using std::ifstream;
using std::unordered_map;
using std::variant;
using std::pair;


class ConfParser {
private:
    decltype(auto) GetValue(const string &key) {
        return dict[key];
    }

    decltype(auto) GetValue(const string &key) const {
        return dict.at(key);
    }

    void ParseFile() {
        string line;
        while (std::getline(fin, line)) {
            std::istringstream curLine(line);
            if (std::string type; std::getline(curLine, type, ':')) {
                if (std::string key; std::getline(curLine, key, '=')) {
                    if (std::string value; std::getline(curLine, value)) {
                        if (type == "int32") {
                            dict[key] = std::stoi(value);
                        } else if (type == "string") {
                            dict[key] = value;
                        }
                    }
                }
            }
        }
    }

public:
    typedef variant<int32_t, string> valueType;

    explicit ConfParser(const string &fileName) : fin(fileName) {
        if (!fin.is_open()) {
            throw std::invalid_argument("file not found");
        }
        ParseFile();
    }

    int32_t GetInt(const string &key) {
        return get<int32_t>(GetValue(key));
    }

    string GetString(const string &key) {
        return get<string>(GetValue(key));
    }

    friend std::ostream &operator<<(std::ostream &stream, const ConfParser &confParser);

private:
    ifstream fin;
    unordered_map<string, valueType> dict;
};

std::ostream &operator<<(std::ostream &stream, const ConfParser &confParser) {
    for (const auto &[key, value]: confParser.dict) {
        stream << "|" << std::left << std::setw(14) << key << "|";
        std::visit([&stream](const auto &val) {
            stream << std::left << std::setw(14) << val << "|\n";
        }, value);
    }
    stream.flush();
    return stream;
}

std::string CONF_PATH = PathManip().ConcatenateByLastPart(PathManip{"HearthtoneConsole/*/core/configurations"});
