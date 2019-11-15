from TSVC.create_tpips import generate_files
from settings import max_unrolling
from settings import tsvc_benchmark_path
from TSVC.apply_unrolling import unroll_all
from settings import tsvc_measurement_path
from settings import optimization
from TSVC.run_exe import execute_all
from settings import  number_of_times
from TSVC.delete import delete_files



delete_files(tsvc_benchmark_path, ".tpips")
generate_files(max_unrolling,tsvc_benchmark_path)
delete_files(tsvc_benchmark_path, ".out")
unroll_all(tsvc_benchmark_path, tsvc_measurement_path, optimization)
execute_all(tsvc_measurement_path, number_of_times)






