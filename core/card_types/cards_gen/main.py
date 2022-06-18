import os
import re
import shutil


def camel_to_snake(name):
    name = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', name).lower()


if __name__ != '__main__':
    raise RuntimeError("This script supposed to run on its own")

LIST_OF_DATA = [["UnitCard", "Unit", 1, 1, 1, "COMMON"], ]

dir_path = os.path.join(os.path.dirname(os.getcwd()), "generated_cards")
print(dir_path)
if os.path.exists(dir_path):
    shutil.rmtree(dir_path)
os.mkdir(dir_path)

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


def generate_header(camel_base, camel_new):
    snake_base = camel_to_snake(camel_base)
    snake_new = camel_to_snake(camel_new)
    with open(os.path.join(dir_path, snake_new + '.h'), 'w') as file:
        write_str = format_template_header.format(base_class_snake=snake_base, new_class_camel=camel_new,
                                                  base_class_camel=camel_base)
        file.write(write_str)


format_template_source = """//
// Created by codegen
//

#include "{new_class_snake}.h"

namespace Core {{
    {new_class_camel}::{new_class_camel}({new_class_arguments}) : {base_class_camel}({new_class_values}) {{

    }}
}}

"""


def generate_arguments_base(lst_of_args):
    type_arg = lst_of_args[-1]
    other_args = []
    for arg in lst_of_args[:-1]:
        if isinstance(arg, int):
            other_args.append(f"{arg}")
        else:
            raise NotImplemented("Unsupported type")
    other_args.append(f"Core::Card::CARD_RARITY::{type_arg}")
    return ", ".join(other_args)


# TODO: add parser base and cur classes
def generate_source(camel_base, camel_new, arguments_base, initialization_list_arguments):
    snake_new = camel_to_snake(camel_new)
    with open(os.path.join(dir_path, snake_new + '.cpp'), 'w') as file:
        write_str = format_template_source.format(new_class_snake=snake_new, new_class_camel=camel_new,
                                                  base_class_camel=camel_base, new_class_arguments=arguments_base,
                                                  new_class_values=initialization_list_arguments)
        file.write(write_str)


# TODO: add cmake file
for ls in LIST_OF_DATA:
    generate_header(ls[0], ls[1])
    generate_source(ls[0], ls[1], "", generate_arguments_base(ls[2:]))
