from settings import tsvc_functions_path
from settings import main_file
import os


def create_tpips(factor, functions_path, folder_name='tsvc'):
    tpips_file = ["delete {}".format(folder_name), "setproperty ABORT_ON_USER_ERROR TRUE",
                  "setproperty MEMORY_EFFECTS_ONLY FALSE", "create  {}  {}".format(folder_name, main_file)]

    with open(functions_path) as f:
        functions = f.readlines()
    functions = [x.strip() for x in functions]

    for function in functions:
        if len(function) > 0:
            tpips_file.append('apply UNROLL[{}]'.format(function))
            tpips_file.append('loop_{}'.format(function))
            tpips_file.append(str(factor))

    tpips_file.append("apply UNSPLIT")
    tpips_file.append("close")
    tpips_file.append("quit")
    return tpips_file


def generate_files(max_factor, path):
    for factor in range(2, max_factor):
        tmp_tpips = create_tpips(factor, tsvc_functions_path)
        filename = 'factor_' + str(factor) + '.tpips'
        with open(os.path.join(path, filename), 'w') as f:
            for item in tmp_tpips:
                f.write("%s\n" % item)



