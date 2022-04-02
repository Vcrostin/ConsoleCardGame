//
// Created by brostin on 19.03.2022.
//

#pragma once
#include <string_view>
#include <vector>
#include <string>
#include <algorithm>


std::vector<std::string_view> string_split(std::string_view str, char delim = ' ');

constexpr std::string_view string_strip(std::string_view stripped_str, char delim = ' ') {
    while (!stripped_str.empty() && stripped_str.starts_with(delim)) {
        stripped_str.remove_prefix(1);
    }
    while (!stripped_str.empty() && stripped_str.ends_with(delim)) {
        stripped_str.remove_suffix(1);
    }
    return stripped_str;
}

std::string multiply_string(std::string_view, size_t);

std::string replace_chars(std::string_view str, char new_delim, char delim = ' ');
