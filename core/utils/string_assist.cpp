//
// Created by brostin on 19.03.2022.
//

#include "string_assist.h"

std::vector<std::string_view> string_split(std::string_view str, char delim) {
    std::vector<std::string_view> splitted_string;
    for (auto begin_it = str.begin(); begin_it != str.end();) {

        if (*begin_it == delim) {
            begin_it++;
            continue;
        }
        auto end_it = begin_it + 1;
        while (end_it != str.end() && *end_it != delim) {
            end_it++;
        }
        // c++ 20 :
        // splitted_string.push_back({str.begin(), str.end()});

        // c++ 17
        auto str_ref = std::string_view(str);
        str_ref.remove_prefix(begin_it - str.begin());
        str_ref.remove_suffix(str.end() - end_it);
        splitted_string.push_back({str_ref});
        begin_it = end_it;
    }
    return splitted_string;
}

std::string multiply_string(std::string_view str, size_t n) {
    std::string res_str;
    res_str.reserve(str.size() * n);
    for (size_t i = 0 ; i < n ; i++) {
        res_str += str;
    }
    return res_str;
}

constexpr inline size_t validate_index(size_t index, std::string_view str) {
    if (index == std::string::npos) {
        return str.size();
    }
    return index;
}

std::string replace_chars(std::string_view str, char new_delim, char delim) {
    std::string res_string;
    res_string.reserve(str.size());
    for (size_t i = 0; !str.empty() ; i ++) {
        size_t index;
        if (i % 2 == 0) {
            index = str.find_first_of(delim);
            index = validate_index(index, str);
            res_string += str.substr(0, index);
        }
        else {
            index = str.find_first_not_of(delim);
            index = validate_index(index, str);
            res_string += multiply_string(std::string(1, new_delim), index);
        }
        str.remove_prefix(index);
    }
    return res_string;
}
