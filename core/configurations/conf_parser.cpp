//
// Created by brostin on 05.06.22.
//

#include "conf_parser.h"


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
