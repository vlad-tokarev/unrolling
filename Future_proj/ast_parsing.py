from pycparser import c_parser, c_ast
from pycparser.c_ast import *

# To get all outer most loops
def get_outer_loops(list_to_traverse,outer_loops = []):
    for elem in list_to_traverse:
        if(elem.__class__ is FuncDef):
            items = elem.body.block_items
            get_outer_loops(items,outer_loops)
        else:
            if(elem.__class__ is For):
                outer_loops.append(elem)
    return outer_loops


#Based on outer most loops, we get inner most loops
def get_inner_loops(outer_loops):
    inner_loops = []
    for loop in outer_loops:
        inner_loops.append(get_single_inner_loop(loop,[]))
    return inner_loops

# These 2 functions help to find the most inner loops
def check_children_for(loop):
    items = loop.stmt.block_items
    for item in items:
        if(item.__class__ is For):
            return True
    return False

def get_single_inner_loop(outer_loop,loops, level = 1):
    if(check_children_for(outer_loop)):
        items = outer_loop.stmt.block_items
        for item in items:
            if(item.__class__ is For):
                get_single_inner_loop(item,loops, level+1)
    else:
        loops.append((outer_loop,level))
    return loops


#to process all inner most loops
def process_loops(nest_list):

    features = {}
    for nest in nest_list:  #process every loop nest
        for deadlock in nest:
            loop = deadlock[0]
            loop_level = deadlock[1]
            number_of_stmt = get_number_of_stmt(loop)
            statements = loop.stmt.block_items

            features[loop] = {'statements': number_of_stmt, 'writes': 0, 'reads': 0, 'level': loop_level, 'arrays': set(), 'vars': set()}
            for stmt in statements:
                if(stmt.__class__ is Assignment):
                    process_lvalue(stmt.lvalue,features,loop)
                    process_rvalue(stmt.rvalue,features,loop)

    for value in features.values():
        number_of_arrays = len(value['arrays'])
        number_of_vars =  len(value['vars'])
        value['arrays'] = number_of_arrays
        value['vars'] = number_of_vars

    return features

def get_number_of_stmt(loop):
    number = len(loop.stmt.block_items)
    return number

def process_arrayref(array_ref, features, loop):
    if(array_ref.__class__ is ID):
        features[loop]['arrays'].add(array_ref.name)
    else:
        process_arrayref(array_ref.name, features, loop)

def process_lvalue(lval,features, loop):
    if (lval.__class__ is ID):
        features[loop]['vars'].add(lval.name)
        features[loop]['writes'] +=1
    else:
        if (lval.__class__ is ArrayRef):
            process_arrayref(lval, features, loop)
            features[loop]['writes'] +=1


def process_rvalue(rval, features, loop):
    if(rval.__class__ is BinaryOp):
        process_rvalue(rval.left, features, loop)
        process_rvalue(rval.right, features, loop)
    else:
        if(rval.__class__ is ID):
            features[loop]['vars'].add(rval.name)
            features[loop]['reads'] += 1
        else:
            if(rval.__class__ is ArrayRef):
                process_arrayref(rval, features, loop)
                features[loop]['reads'] += 1

def get_features(text):
    parser = c_parser.CParser()
    ast = parser.parse(text, filename='<none>')
    outer_loops = get_outer_loops(ast.ext)
    inner_loops = get_inner_loops(outer_loops)
    features = process_loops(inner_loops)
    return features





