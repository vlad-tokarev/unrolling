def get_content(file):
    with open(file) as f:
        raw_strings = f.readlines()
    raw_strings = [x.strip() for x in raw_strings]
    content = []
    for item in raw_strings:
        content.append(item.split(' '))
    for item in content:
        item.remove('-')
    return content

def get_carried_dependency_vectors(content):
    vectors = []
    for i in range(len(content)):
            if(content[i][-1].__contains__('uniform')):
                tmp = content[i][-1]
                value = tmp[tmp.index('(')+1:tmp.index(')')]
                value = value.split(',')
                dimension = len(value)
                for k in range(dimension):
                    value[k] = int(value[k])
                dimension = len(value)
                dependence = content[i][dimension] + content[i][dimension+1] #RW
                value.append(dependence)
                value.append(content[i][dimension+2]) # array name
                vectors.append(value)
    return vectors

def get_not_carried_dependency_vector(content):
    vectors = []
    for i in range(len(content)):
            if(not content[i][-1].__contains__('uniform')):
                dependence = content[i][2] + content[i][3]
                vectors.append([dependence,content[i][4]])
    return vectors

def features(file):
    feature_dict = {}
    content  = get_content(file)
    carried_vector = get_carried_dependency_vectors(content)
    not_carried_vector = get_not_carried_dependency_vector(content)
    feature_dict['Number_of_carried_dependencies'] = len(carried_vector)
    feature_dict['Number_of_not_carried_dependencies'] = len(not_carried_vector)
    feature_dict['Number_of_carried_WW'] , feature_dict['Number_of_carried_RW'] , feature_dict['Number_of_carried_WR'] , feature_dict['Number_of_carried_RR'] = get_amout_of_dependencies(carried_vector)
    feature_dict['Number_of_not_carried_WW'] , feature_dict['Number_of_not_carried_RW'] , feature_dict['Number_of_not_carried_WR'] , feature_dict['Number_of_not_carried_RR'] = get_amout_of_dependencies(not_carried_vector)


    sets_of_array = get_involved_arrays(carried_vector,not_carried_vector)
    number_of_arrs_and_vars = [0,0,0]
    for idx, item in enumerate(sets_of_array):
        number_of_arrs_and_vars[idx] = len(item)

    feature_dict['Involved_carried_arrays'], feature_dict['Involved_not_carried_arrays'], feature_dict['Involved_not_carried_vars']  = number_of_arrs_and_vars

    feature_dict['Vectors'] = carried_vector

    return feature_dict

def get_amout_of_dependencies(list):
    amount = [0]*4
    deps = ['WW','RW','WR', 'RR']
    for item in list:
        for idx, val in enumerate(deps):
            if(val in item):
                amount[idx] +=1
    return amount

def get_involved_arrays(carried_list, not_carried_list):
    used_carried_arrays = set()
    used_not_carried_arrays = set()
    used_not_carried_vars = set()
    for i in range(len(carried_list)):
        array = carried_list[i][-1]
        used_carried_arrays.add(array[1:array.index('[')])
    for i in range(len(not_carried_list)):
        array = not_carried_list[i][-1]
        if('[' in array):
            used_not_carried_arrays.add(array[1:array.index('[')])
        else:
            used_not_carried_vars.add(array[1:-1])
    return used_carried_arrays, used_not_carried_arrays, used_not_carried_vars