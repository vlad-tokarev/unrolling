import os

from settings import MEASUREMENTS
from settings import TRANSFORMED
from settings import BENCHMARK
from settings import optimization
from settings import main_file
from settings import temp_file

from TSVC.add_new_main import add_new_main

os.chdir(BENCHMARK)
for file in os.listdir(BENCHMARK):
    if file.endswith(".tpips"):
        factor = file[file.index('_') + 1:file.index('.')]  # get unrolling factor based on a file name
        tmp_file = os.path.join(BENCHMARK, file)
        os.system("tpips {}".format(tmp_file))
        old_name = os.path.join(TRANSFORMED, main_file)
        os.system('mv {} {}'.format(old_name, temp_file))

        for i in range(5):
            add_new_main(temp_file, "main_{}".format(str(i)))
            os.system('cat includes.txt {} time.txt > output.c'.format(temp_file))
            name = 'a_' + factor + '_' + str(i) + '.out'
            output_path = os.path.join(MEASUREMENTS, name)
            os.system(
                'gcc {} output.c dummy.c common.c `papiex-config --cflags --libs` -o {} -lm'.format(optimization,
                                                                                                    output_path))
