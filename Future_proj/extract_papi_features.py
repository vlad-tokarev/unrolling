import regex as re
import os
import pandas as pd
from strings_and_commands import feature_string
from settings import MEASUREMENTS_PATH


keys = feature_string.split('\n')
function_keys = keys[26:]
kernel_keys = keys[:26]



def get_all_files(path):
    files = []
    for file in os.listdir(path):
        if file.endswith(".txt") and file.__contains__("report"):
            files.append(os.path.join(path, file))
    list_of_content = []
    for file in files:
        with open(file) as f:
            content = f.readlines()
        content = [x.strip() for x in content]
        list_of_content.append(content)

    return list_of_content

def get_measurements(list_of_content):

    pattern = r"\[s.*?\]"
    kernel_martice_dict = {}

    for content in list_of_content:
        matrice_number = content[2][content[2].rfind('/')+1 :]
        for line in content:
            result = re.findall(pattern,line)
            if(len(result)>0):
                kernel_number = result[0][1:-1]
                current_feature = float(line[line.rfind('.') - 1:])
                feature_name = line[line.find(']')+2:line.find('.')-1]
                if(not (matrice_number,kernel_number) in kernel_martice_dict.keys()):
                    kernel_martice_dict[(matrice_number, kernel_number)] = {}
                    for key in function_keys:
                        kernel_martice_dict[(matrice_number,kernel_number)][key] = []
                kernel_martice_dict[(matrice_number, kernel_number)][feature_name].append(current_feature)

    for key in kernel_martice_dict.keys():
        for subkey in kernel_martice_dict[key]:
            tmp = sum(kernel_martice_dict[key][subkey])/len(kernel_martice_dict[key][subkey])
            kernel_martice_dict[key][subkey] = tmp
    return kernel_martice_dict

def get_dataframe(dictionary):
    X = []
    function = []
    matrix = []
    for key in dictionary.keys():
        X.append(dictionary[key])
        function.append(key[0])
        matrix.append(key[1])
    X = pd.DataFrame.from_records(X)
    X.columns = function_keys
    X.insert(loc=0, column='Matrix', value=matrix)
    X.insert(loc=0, column='Loop', value=function)
    return X







