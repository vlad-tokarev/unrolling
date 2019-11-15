import os
import datetime
from settings import MEASUREMENTS
from settings import number_of_times


def get_timestamp():
    return datetime.datetime.now().timestamp()


os.chdir(MEASUREMENTS)

for file in os.listdir(MEASUREMENTS):
    if file.endswith(".out"):
        factor = file[2:file.index('.') - 2]  # get unrolling factor based on a file name
        for i in range(number_of_times):
            results = factor + '_' + str(get_timestamp()) + '.txt'
            os.system('papiex -a ./{} > {}'.format(file, results))
