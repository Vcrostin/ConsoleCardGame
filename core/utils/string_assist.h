//
// Created by brostin on 19.03.2022.
//

#pragma once

#include <string_view>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

using boost::uuids::detail::md5;


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

std::vector<std::string_view> string_split(std::string_view, uint32_t);

//TODO: move to different file
inline std::string toString(const md5::digest_type &digest) {
    const auto charDigest = reinterpret_cast<const char *>(&digest);
    std::string result;
    boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(result));
    return result;
}
