

def change_file(filename):

    with open(filename) as f:
        content = f.readlines()
    new_content = []

    last_bracket = 0
    number_of_opened_brackets = 0
    current_loop = 1
    pragma = False

    for index, element in enumerate(content):

        if(pragma == False):
            if('pragma' in element):
                pragma = not pragma
            new_content.append(element)
        else:
            if('for (' in element and number_of_opened_brackets == 0):
                if(current_loop!=1):
                    #new_content.append("polybench_stop_instruments;\n")
                    #new_content.append("polybench_print_instruments;\n")
                    #new_content.append("PAPIEX_STOP_ARG({});\n".format(str(current_loop-1)))

                #new_content.append("PAPIEX_START_ARG({}, \"loop_{}\");\n".format(str(current_loop), str(current_loop)))
                #new_content.append("polybench_start_instruments;\n")
                #new_content.append(element)
                current_loop+=1
                if ('{' in element):
                    number_of_opened_brackets += 1
            else:
                if('{' in element):
                    number_of_opened_brackets +=1
                    new_content.append(element)

                else:
                    if('}' in element):
                        number_of_opened_brackets -=1
                        new_content.append(element)


                    else:
                        new_content.append(element)
                        if("pragma" in element):
                            pragma = not pragma





    indexes = []
    for ind, elem in enumerate(new_content):
        if('for (' in elem):
            tmp_index = ind

        if("polybench_stop_instruments;" in elem):
            indexes.append(tmp_index)


    for ind, elem in enumerate(indexes):
        new_content.insert(elem+ind,'loop_{}:'.format(str(ind+1)))


    new_content.insert(0,'#include \"papiex.h\"\n')

    number_of_pragmas = 0
    br = 0
    for indexx, line in enumerate(new_content):
        if('pragma' in line):
            number_of_pragmas+=1
        if(number_of_pragmas == 1 and '}' in line):
            br = indexx

    new_content.insert(br+1,"polybench_stop_instruments;\n" )
    new_content.insert(br+2,"polybench_print_instruments;\n" )
    new_content.insert(br+3,"PAPIEX_STOP_ARG({});\n".format(str(current_loop-1)))


    with open(filename, 'w+') as f:
        for item in new_content:
            f.write("%s" % item)



import os

p = '/home/maksim/PycharmProjects/poly/polybench-c-4.2.1-beta'

with open('/home/maksim/PycharmProjects/poly/polybench-c-4.2.1-beta/utilities/benchmark_list') as f:
    content = f.readlines()
content = [x.strip() for x in content]

for file in content:
    change_file(os.path.join(p,file[2:]))

