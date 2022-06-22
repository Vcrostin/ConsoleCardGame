from utils import camel_to_snake, generate_title
import os

additional_includes = """#include <utility>
#include <unordered_map>
#include <functional>
"""

format_template_include = """#include "{include}"
"""

OUT_FILE_NAME = "all_generated_classes"

format_template_function_header = """
inline std::shared_ptr<Core::{new_class}> Make{new_class}() {{
    return std::make_shared<Core::{new_class}>();
}}"""

format_template_all_elem_hashtable_header = """
extern std::unordered_map<int32_t, std::function<std::shared_ptr<Core::Card>()>> HashTable;"""

format_template_all_elem_hashtable_source = """
std::unordered_map<int32_t, std::function<std::shared_ptr<Core::Card>()>> GeneratedCard::HashTable = {{{key_value_pair}
}};
"""

NAMESPACE_NAME = "GeneratedCard"
NAMESPACE_INDENT = 4


class GenerateAllClasses:
    def __init__(self):
        self.classes = []

    def add_class(self, class_name):
        self.classes.append(class_name)

    def generate_file(self, dir_path):
        includes_lst = []
        for cls in self.classes:
            header_name = camel_to_snake(cls)
            includes_lst.append(header_name + '.h')

        with open(os.path.join(dir_path, f'{OUT_FILE_NAME}.h'), 'w') as file:
            file.write(generate_title + "\n\n")
            file.write(additional_includes)
            file.writelines(list(map(lambda x: format_template_include.format(include=x), includes_lst)))
            file.write(f"""\nnamespace {NAMESPACE_NAME} {{\n""")
            for cls in self.classes:
                file.write(('\n' + ' ' * NAMESPACE_INDENT).join(
                    format_template_function_header.format(new_class=cls).split('\n')))
                file.write('\n')
            file.write(('\n' + ' ' * NAMESPACE_INDENT).join(
                format_template_all_elem_hashtable_header.split('\n')))
            file.write('\n')
            file.write("}\n")

        key_value_list = [""]
        id_counter = 1
        for cls in self.classes:
            key_value_list.append(f"{{{id_counter}, Make{cls}}},")
            id_counter += 1

        with open(os.path.join(dir_path, f'{OUT_FILE_NAME}.cpp'), 'w') as file:
            file.write(generate_title + "\n\n")
            file.write(f'#include "{OUT_FILE_NAME}.h"\n')
            file.write(
                format_template_all_elem_hashtable_source.format(
                    key_value_pair=('\n' + ' ' * 2 * NAMESPACE_INDENT).join(key_value_list)))
