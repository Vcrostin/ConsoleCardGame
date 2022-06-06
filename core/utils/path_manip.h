//
// Created by brostin on 06.06.22.
//

#pragma once

#include <filesystem>
#include <functional>
#include <string>
#include <string_view>
#include <vector>
#include "string_assist.h"

using std::string;
using std::string_view;

/// TODO: Add concatenate path function
class PathManip {
public:
    explicit PathManip(const string &path = std::filesystem::current_path()) {
        ParsePath();
    }

private:
    void ParsePath() {
        auto pathSplitted = string_split(curPath, '/');
        size_t prevHash = 0;
        for (auto pathPart: pathSplitted) {
            pathNodes.emplace_back(PathNode{pathPart, prevHash});
            prevHash = pathNodes.back().partHash;
        }
    }

    struct PathNode {
        std::string pathPart;
        size_t partHash;
        size_t sumHash;

        explicit PathNode(string_view pathPart, size_t previousHash) : pathPart(pathPart) {
            Hash(pathPart, previousHash);
        }

    private:
        void Hash(string_view str, size_t previousHash) {
            partHash = std::hash<string_view>{}(str);
            sumHash = std::hash<string_view>{}(str) + previousHash;
        }
    };

    std::vector<PathNode> pathNodes;

    string curPath;
};


