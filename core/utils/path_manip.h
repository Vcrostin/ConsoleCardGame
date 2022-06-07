//
// Created by brostin on 06.06.22.
//

#pragma once

#include <algorithm>
#include <filesystem>
#include <functional>
#include <string>
#include <string_view>
#include <vector>
#include "string_assist.h"

using std::string;
using std::string_view;

class PathManip {
public:
    explicit PathManip(const string &path = std::filesystem::current_path()) : curPath(path) {
        ParsePath();
    }

    string ConcatenateAbsolute(const PathManip &pm) {
        for (int64_t i = static_cast<int64_t>(std::min(pm.pathNodes.size(), this->pathNodes.size())); i >= 0; --i) {
            if (pm.pathNodes[i].sumHash == this->pathNodes[i].sumHash &&
                pm.pathNodes[i].partHash == this->pathNodes[i].partHash &&
                pm.pathNodes[i].pathPart == this->pathNodes[i].pathPart) {
                this->pathNodes.erase(this->pathNodes.begin() + i + 1, this->pathNodes.end());
                for (int64_t j = i + 1; j < static_cast<int64_t>(pm.pathNodes.size()); ++j) {
                    this->pathNodes.emplace_back(pm.pathNodes[j]);
                }
                curPath = "";
                for (const auto &s: this->pathNodes) {
                    curPath += "/" + s.pathPart;
                }
                return curPath;
            }
        }
        curPath = pm.curPath;
        pathNodes = pm.pathNodes;
        return curPath;
    }

    string ConcatenateByLastPart(const PathManip &pm) {
        for (int64_t i = static_cast<int64_t>(this->pathNodes.size()); i >= 0; --i) {
            if (pm.pathNodes.front().partHash == this->pathNodes[i].partHash &&
                pm.pathNodes.front().pathPart == this->pathNodes[i].pathPart) {
                size_t shift = 1;
                while (pm.pathNodes.size() > shift && pm.pathNodes[shift].pathPart == "*") {
                    ++shift;
                }
                this->pathNodes.erase(this->pathNodes.begin() + i + shift, this->pathNodes.end());
                for (int64_t j = shift; j < static_cast<int64_t>(pm.pathNodes.size()); ++j) {
                    this->pathNodes.emplace_back(pm.pathNodes[j]);
                }
                curPath = "";
                for (const auto &s: this->pathNodes) {
                    curPath += "/" + s.pathPart;
                }
                return curPath;
            }
        }
        return curPath;
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


