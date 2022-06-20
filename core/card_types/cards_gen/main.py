from utils import camel_to_snake, get_mariadb_list, dir_recreate
from generate_header import generate_header
from generate_source import generate_source
from generate_cmake import generate_cmake

if __name__ != '__main__':
    raise RuntimeError("This script supposed to run on its own")

LIST_OF_DATA = get_mariadb_list()

DIR_PATH = dir_recreate("generated_cards")

source_files = []
for ls in LIST_OF_DATA:
    generate_header(ls[0], ls[1], DIR_PATH)
    generate_source(ls[0], ls[1], "", ls[2:], DIR_PATH)
    file_name = camel_to_snake(ls[1])
    source_files.append([file_name + '.cpp', file_name + '.h'])
generate_cmake(source_files, DIR_PATH)
