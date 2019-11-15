import os

PROJECT_PATH = os.path.dirname(os.path.abspath(__file__))

main_file = 'tsvc_new.c'
temp_file = 'tsvc_tmp.c'
max_unrolling = 31
optimization = '-O0'
number_of_times = 2


tsvc_path = os.path.join(PROJECT_PATH, 'TSVC')
tsvc_measurement_path = os.path.join(tsvc_path, 'Measurements')
tsvc_benchmark_path = os.path.join(tsvc_path, 'Benchmark', 'src')
tsvc_functions_path = os.path.join(tsvc_benchmark_path, 'functions.txt')
tsvc_transformed_path = os.path.join(tsvc_benchmark_path, 'tsvc.database', 'Src')




