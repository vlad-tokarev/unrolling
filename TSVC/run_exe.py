import os
import datetime


def get_timestamp():
    return datetime.datetime.now().timestamp()


def execute_all(path, n):
    os.chdir(path)
    for file in os.listdir(path):
        if file.endswith(".out"):
            factor = file[2:file.index('.') - 2]  # get unrolling factor based on a file name
            for i in range(n):
                results = factor + '_' + str(get_timestamp()) + '.txt'
                os.system('papiex -a ./{} > {}'.format(file, results))
