import os

format_template_cmake = """project(generated_cards)

add_library(GeneratedCards
{source_files})
"""


# TODO add all_new_classes_include file
def generate_cmake(source_files, dir_path):
    with open(os.path.join(dir_path, 'CMakeLists.txt'), 'w') as file:
        write_str = format_template_cmake.format(
            source_files='\n'.join(list(map(lambda x: ' ' * 8 + ' '.join(x), source_files))))
        file.write(write_str)
