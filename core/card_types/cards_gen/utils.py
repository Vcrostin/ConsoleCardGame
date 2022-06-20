import re
import mariadb
import sys
import json
import os
import shutil


def camel_to_snake(name):
    name = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', name).lower()


def get_mariadb_list():
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
    list_of_data = []
    for x in rows:
        j = json.loads(x[3])
        list_of_data.append(list(x[1:3]))
        for el in j:
            list_of_data[-1].append(el)
    return list_of_data


def dir_recreate(dir_name):
    dir_path = os.path.join(os.path.dirname(os.getcwd()), dir_name)
    print(dir_path)
    if os.path.exists(dir_path):
        shutil.rmtree(dir_path)
    os.mkdir(dir_path)
    return dir_path
