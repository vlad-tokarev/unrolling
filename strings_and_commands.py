

pips_source = "source /home/maksim/papiex-oss/papiex-oss-install/papiex-oss.sh"
papiex_first = "sudo sh -c \"echo 0 > /proc/sys/kernel/perf_event_paranoid\""
papiex_second = "sudo sh -c \"echo 0 > /proc/sys/kernel/yama/ptrace_scope\""
compilation_string_tsvc = "gcc -O3 tsvc.c dummy.c common.c `papiex-config --cflags --libs` -o output"
get_results = "papiex -a ./output"






feature_string = """IPC
Load Store Ratio
Instructions Per Dcache Miss
Wallclock seconds
No Issue Stall seconds
Resource Stall seconds
Cycles In Domain
Real Cycles
Running Time In Domain
Virtual Cycles
Total Instructions
Memory Instructions
Memory Instructions
Branch Instructions
Load Store Ratio
L1 Data Misses Per 1000 Load Stores
L1 Data Misses Per 1000 Load Stores
L1 Instruction Misses Per 1000 Instructions
L2 Data Misses Per 1000 L2 Load Stores
L2 Instruction Misses Per 1000 L2 Instructions
Data TLB Misses Per 1000 Load Stores Instruction
TLB Misses Per 1000 Instructions
Resource Stall Cycles
No Issue Cycle
Full Issue Cycle
Branch Misprediction
Measurements
PAPI_BR_CN
PAPI_BR_INS
PAPI_BR_MSP
PAPI_FUL_ICY
PAPI_L1_DCM
PAPI_L1_ICM
PAPI_L2_DCA
PAPI_L2_DCM
PAPI_L2_ICA
PAPI_L2_ICM
PAPI_LD_INS
PAPI_LST_INS
PAPI_RES_STL
PAPI_SR_INS
PAPI_STL_ICY
PAPI_TLB_DM
PAPI_TLB_IM
PAPI_TOT_CYC
PAPI_TOT_INS
Real cycles"""