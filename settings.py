import os

PROJECT_PATH = os.path.dirname(os.path.abspath(__file__))


MEASUREMENTS_PATH = os.path.join(PROJECT_PATH,'Measurements')
MEASUREMENTS_TSVC_PATH = os.path.join(MEASUREMENTS_PATH,'TSVC2_original')



TSVC_FUNCTIONS_PATH  = os.path.join(PROJECT_PATH,'Benchmarks','TSVC2_original', 'src', 'functions.txt')
TSVC_PATH =  os.path.join(PROJECT_PATH,'Benchmarks','TSVC2_original', 'src')
TSVC_AFTER_PIPS =  os.path.join(TSVC_PATH, 'tsvc.database', 'Src')


tscv_main_file = 'tsvc_new.c'
tscv_temp_file = 'tsvc_tmp.c'