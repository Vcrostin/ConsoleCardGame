//
// Created by brostin on 05.06.22.
//

#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
#include <variant>
#include <utility>
#include <iostream>
#include <sstream>

using std::string;
using std::ifstream;
using std::unordered_map;
using std::variant;
using std::pair;


class ConfParser {
private:
    decltype(auto) GetValue (const string& key) {
        return dict[key];
    }

    decltype(auto) GetValue (const string& key) const {
        return dict.at(key);
    }

    void ParseFile() {
        string line;
        while(std::getline(fin, line)) {
            std::istringstream curLine(line);
            if (std::string type; std::getline(curLine, type, ':')) {
                if (std::string key; std::getline(curLine, type, '=')) {
                    if (std::string value; std::getline(curLine, value)) {
                        if (type == "int32") {
                            dict[key] = std::stoi(value);
                        }
                        else if (type == "string") {
                            dict[key] = value;
                        }
                    }
                }
            }
        }
    }
public:
    typedef variant<int32_t, string> valueType;
    explicit ConfParser(const string& fileName) : fin(fileName) {
        ParseFile();
    }

    int32_t GetInt(const string& key) {
        return get<int32_t>(GetValue(key));
    }

    string GetString(const string& key) {
        return get<string>(GetValue(key));
    }
private:
    ifstream fin;
    unordered_map<string, valueType> dict;
};


