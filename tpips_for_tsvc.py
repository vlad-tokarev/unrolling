from settings import TSVC_FUNCTIONS_PATH
from settings import TSVC_PATH
from settings import tscv_main_file
import os

max_unrolling = 31
def create_tpips_for_tsvc(factor, functions_path,foldername ='tsvc'):

    tpips_file = []
    tpips_file.append("delete {}".format(foldername))
    tpips_file.append("setproperty ABORT_ON_USER_ERROR TRUE")
    tpips_file.append("setproperty MEMORY_EFFECTS_ONLY FALSE")
    tpips_file.append("create  {}  tsvc_new.c".format(foldername))

    with open(functions_path) as f:
        functions = f.readlines()
    functions = [x.strip() for x in functions]

    for function in functions:
        if(len(function)>0):
            tpips_file.append('apply UNROLL[{}]'.format(function))
            tpips_file.append('loop_{}'.format(function))
            tpips_file.append(str(factor))

    tpips_file.append("apply UNSPLIT")
    tpips_file.append("close")
    tpips_file.append("quit")
    return tpips_file

def generate_files(max_factor, path):
    for factor in range(2,max_factor):
        tmp_tpips = create_tpips_for_tsvc(factor,TSVC_FUNCTIONS_PATH)
        filename = 'factor_' + str(factor) + '.tpips'
        with open(os.path.join(path,filename), 'w') as f:
            for item in tmp_tpips:
                f.write("%s\n" % item)

generate_files(max_unrolling,TSVC_PATH)

