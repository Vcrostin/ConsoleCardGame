from utils import camel_to_snake, generate_title
import os

format_template_source = generate_title + """

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


def generate_source(camel_base, camel_new, arguments_base, initialization_list_arguments, dir_path):
    initialization_list_arguments = generate_arguments_base(initialization_list_arguments)
    snake_new = camel_to_snake(camel_new)
    with open(os.path.join(dir_path, snake_new + '.cpp'), 'w') as file:
        write_str = format_template_source.format(new_class_snake=snake_new, new_class_camel=camel_new,
                                                  base_class_camel=camel_base, new_class_arguments=arguments_base,
                                                  new_class_values=initialization_list_arguments)
        file.write(write_str)
