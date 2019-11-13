

with open('/home/maksim/PycharmProjects/tilin/Benchmarks/TSVC2_original/src/tsvc_preprocessed.c') as f:
    raw_strings = f.readlines()
raw_strings = [x.strip() for x in raw_strings]
content = []


f = []

for i in range(len(raw_strings)):
    if('(struct args_t *func_args)' in raw_strings[i]):
        if(not 'extern' in raw_strings[i]):
            name = raw_strings[i][raw_strings[i].index(' ')+1: raw_strings[i].index('(')]
    if('for' in raw_strings[i]):
        tmp = i
    if('return calc_checksum(__func__)' in raw_strings[i]):
        tmp_val =  'loop_' +name +': ' + raw_strings[tmp]
        raw_strings[tmp] = tmp_val

    print(i)


with open('labeled_tsvc.c', 'w') as f:
    for item in raw_strings:
        f.write("%s\n" % item)


