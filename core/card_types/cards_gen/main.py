import os
import re
import shutil
import mariadb
import sys
import json


# TODO: split into separate files
def camel_to_snake(name):
    name = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', name).lower()


if __name__ != '__main__':
    raise RuntimeError("This script supposed to run on its own")

try:
    conn_params = {
        'user': "guest",
        'host': "45.141.101.11",
        'port': 3306,
        'database': "card_gen",
        'password': "guest_password",
    }

    # establish a connection
    connection = mariadb.connect(**conn_params)
    cursor = connection.cursor()
except mariadb.Error as e:
    print(f"Error connecting to the database: {e}")
    sys.exit(1)
query = f"SELECT * FROM card_gen"
cursor.execute(query)
rows = cursor.fetchall()
connection.close()
LIST_OF_DATA = []
for x in rows:
    j = json.loads(x[3])
    LIST_OF_DATA.append(list(x[1:3]))
    for el in j:
        LIST_OF_DATA[-1].append(el)

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


def generate_source(camel_base, camel_new, arguments_base, initialization_list_arguments):
    snake_new = camel_to_snake(camel_new)
    with open(os.path.join(dir_path, snake_new + '.cpp'), 'w') as file:
        write_str = format_template_source.format(new_class_snake=snake_new, new_class_camel=camel_new,
                                                  base_class_camel=camel_base, new_class_arguments=arguments_base,
                                                  new_class_values=initialization_list_arguments)
        file.write(write_str)


format_template_cmake = """project(generated_cards)

add_library(GeneratedCards
{source_files})
"""


# TODO add all_new_classes_include file
def generate_cmake(source_files):
    with open(os.path.join(dir_path, 'CMakeLists.txt'), 'w') as file:
        write_str = format_template_cmake.format(source_files='\n'.join(list(map(lambda x: ' '*8 + ' '.join(x), source_files))))
        file.write(write_str)


source_files = []
for ls in LIST_OF_DATA:
    generate_header(ls[0], ls[1])
    generate_source(ls[0], ls[1], "", generate_arguments_base(ls[2:]))
    file_name = camel_to_snake(ls[1])
    source_files.append([file_name + '.cpp', file_name + '.h'])
generate_cmake(source_files)
