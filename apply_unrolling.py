import os
import datetime
from settings import TSVC_PATH
from settings import TSVC_AFTER_PIPS
from settings import tscv_main_file
from settings import tscv_temp_file
from add_new_main import add_new_main

optimization = '-O0'

os.chdir(TSVC_PATH)
for file in os.listdir(TSVC_PATH):
    if file.endswith(".tpips"):
        factor = file[file.index('_')+1:file.index('.')] #get unrolling factor based on a file name
        tmp_file = os.path.join(TSVC_PATH, file)
        os.system("tpips {}".format(tmp_file))
        old_name = os.path.join(TSVC_AFTER_PIPS, tscv_main_file)
        os.system('mv {} {}'.format(old_name, tscv_temp_file ))

        for i in range(5):
            add_new_main(tscv_temp_file,"main_{}".format(str(i)))
            os.system('cat includes.txt {} time.txt > output.c'.format(tscv_temp_file))
            name = 'a_'+factor + '_' + str(i)+ '.out'
            os.system('gcc {} output.c dummy.c common.c `papiex-config --cflags --libs` -o {} -lm'.format(optimization,name))



