import os
import datetime
from settings import TSVC_PATH
from settings import MEASUREMENTS_TSVC_PATH

times = 1

def get_timestamp():
    return datetime.datetime.now().timestamp()


os.chdir(TSVC_PATH)


for file in os.listdir(TSVC_PATH):
    if file.endswith(".out"):
        factor = file[2:file.index('.')-2] #get unrolling factor based on a file name
        for i in range(times):
            results = factor + '_' + str(get_timestamp()) + '.txt'
            path_results = os.path.join(MEASUREMENTS_TSVC_PATH, results)
            os.system('papiex -a ./{} > {}'.format(file,path_results))




