from utils import camel_to_snake
import os

format_template_header = """//
// Created by codegen
//
#pragma once

#include "../card_type.h"
#include "../{base_class_snake}.h"

namespace Core {{
    class {new_class_camel} : public Core::{base_class_camel} {{
    public:
        {new_class_camel}();
    }};
}}
"""


def generate_header(camel_base, camel_new, dir_path):
    snake_base = camel_to_snake(camel_base)
    snake_new = camel_to_snake(camel_new)
    with open(os.path.join(dir_path, snake_new + '.h'), 'w') as file:
        write_str = format_template_header.format(base_class_snake=snake_base, new_class_camel=camel_new,
                                                  base_class_camel=camel_base)
        file.write(write_str)
