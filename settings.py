import os

PROJECT_PATH = os.path.dirname(os.path.abspath(__file__))

main_file = 'tsvc_new.c'
temp_file = 'tsvc_tmp.c'
max_unrolling = 31
optimization = '-O0'
number_of_times = 2

TSVC_PATH = os.path.join(PROJECT_PATH, 'TSVC')
MEASUREMENTS = os.path.join(TSVC_PATH, 'Measurements')
BENCHMARK = os.path.join(TSVC_PATH, 'Benchmark', 'src')
FUNCTIONS = os.path.join(BENCHMARK, 'functions.txt')
TRANSFORMED = os.path.join(BENCHMARK, 'tsvc.database', 'Src')




