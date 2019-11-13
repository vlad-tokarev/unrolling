text1 = r"""time_function(&s000, (void *) 0);
time_function(&s111, (void *) 0);
time_function(&s1111, (void *) 0);
time_function(&s112, (void *) 0);
time_function(&s1112, (void *) 0);
time_function(&s113, (void *) 0);
time_function(&s1113, (void *) 0);
time_function(&s114, (void *) 0);
time_function(&s115, (void *) 0);
time_function(&s1115, (void *) 0);
time_function(&s116, (void *) 0);
time_function(&s118, (void *) 0);
time_function(&s119, (void *) 0);
time_function(&s1119, (void *) 0);
time_function(&s121, (void *) 0);
time_function(&s122, &((struct {int a; int b;} ) {n1, n3}));
time_function(&s123, (void *) 0);
time_function(&s124, (void *) 0);
time_function(&s125, (void *) 0);
time_function(&s126, (void *) 0);
time_function(&s127, (void *) 0);
time_function(&s128, (void *) 0);
time_function(&s131, (void *) 0);
time_function(&s132, (void *) 0);
time_function(&s141, (void *) 0);
time_function(&s151, (void *) 0);
time_function(&s152, (void *) 0);
time_function(&s162, &n1);
time_function(&s171, &n1);
time_function(&s172, &((struct {int a; int b;} ) {n1, n3}));
"""
text2 = r"""time_function(&s173, (void *) 0);
time_function(&s174, &((struct {int a;} ) {32000/2}));
time_function(&s175, &n1);
time_function(&s176, (void *) 0);
time_function(&s211, (void *) 0);
time_function(&s212, (void *) 0);
time_function(&s1213, (void *) 0);
time_function(&s221, (void *) 0);
time_function(&s1221, (void *) 0);
time_function(&s222, (void *) 0);
time_function(&s231, (void *) 0);
time_function(&s232, (void *) 0);
time_function(&s1232, (void *) 0);
time_function(&s233, (void *) 0);
time_function(&s2233, (void *) 0);
time_function(&s235, (void *) 0);
time_function(&s241, (void *) 0);
time_function(&s242, &((struct {real_t a; real_t b;} ) {s1, s2}));
time_function(&s243, (void *) 0);
time_function(&s244, (void *) 0);
time_function(&s1244, (void *) 0);
time_function(&s2244, (void *) 0);
time_function(&s251, (void *) 0);
time_function(&s1251, (void *) 0);
time_function(&s2251, (void *) 0);
time_function(&s3251, (void *) 0);
time_function(&s252, (void *) 0);
time_function(&s253, (void *) 0);
time_function(&s254, (void *) 0);
time_function(&s255, (void *) 0);
"""

text3 = """"time_function(&s256, (void *) 0);
time_function(&s257, (void *) 0);
time_function(&s258, (void *) 0);
time_function(&s261, (void *) 0);
time_function(&s271, (void *) 0);
time_function(&s272, &s1);
time_function(&s273, (void *) 0);
time_function(&s274, (void *) 0);
time_function(&s275, (void *) 0);
time_function(&s2275, (void *) 0);
time_function(&s276, (void *) 0);
time_function(&s1279, (void *) 0);
time_function(&s2710, &s1);
time_function(&s2711, (void *) 0);
time_function(&s2712, (void *) 0);
time_function(&s281, (void *) 0);
time_function(&s1281, (void *) 0);
time_function(&s291, (void *) 0);
time_function(&s292, (void *) 0);
time_function(&s293, (void *) 0);
time_function(&s2101, (void *) 0);
time_function(&s2102, (void *) 0);
time_function(&s2111, (void *) 0);
time_function(&s311, (void *) 0);
time_function(&s31111, (void *) 0);
time_function(&s312, (void *) 0);
time_function(&s313, (void *) 0);
time_function(&s314, (void *) 0);
time_function(&s315, (void *) 0);
time_function(&s316, (void *) 0);
"""
text4 = r"""time_function(&s317, (void *) 0);
time_function(&s319, (void *) 0);
time_function(&s3110, (void *) 0);
time_function(&s13110, (void *) 0);
time_function(&s3111, (void *) 0);
time_function(&s3112, (void *) 0);
time_function(&s3113, (void *) 0);
time_function(&s321, (void *) 0);
time_function(&s322, (void *) 0);
time_function(&s323, (void *) 0);
time_function(&s331, (void *) 0);
time_function(&s341, (void *) 0);
time_function(&s342, (void *) 0);
time_function(&s343, (void *) 0);
time_function(&s351, (void *) 0);
time_function(&s1351, (void *) 0);
time_function(&s352, (void *) 0);
time_function(&s353, ip);
time_function(&s421, (void *) 0);
time_function(&s1421, (void *) 0);
time_function(&s422, (void *) 0);
"""
text5 = r""""time_function(&s423, (void *) 0);
time_function(&s424, (void *) 0);
time_function(&s431, (void *) 0);
time_function(&s441, (void *) 0);
time_function(&s451, (void *) 0);
time_function(&s452, (void *) 0);
time_function(&s453, (void *) 0);
time_function(&s471, (void *) 0);
time_function(&s481, (void *) 0);
time_function(&s491, ip);
time_function(&s4112, &((struct {int *a; real_t b;} ) {ip, s1}));
time_function(&s4113, ip);
time_function(&s4114, &((struct {int *a; int b;} ) {ip, n1}));
time_function(&s4115, ip);
time_function(&s4116, &((struct {int *a; int b; int c;} ) {ip, 256/2, n1}));
time_function(&s4117, (void *) 0);
time_function(&s4121, (void *) 0);
time_function(&va, (void *) 0);
time_function(&vag, ip);
time_function(&vas, ip);
time_function(&vif, (void *) 0);
time_function(&vpv, (void *) 0);
time_function(&vtv, (void *) 0);
time_function(&vpvtv, (void *) 0);
time_function(&vpvts, &s1);
time_function(&vpvpv, (void *) 0);
time_function(&vtvtv, (void *) 0);
time_function(&vsumr, (void *) 0);
time_function(&vdotr, (void *) 0);
time_function(&vbor, (void *) 0);
"""

data = [[],[],[],[],[]]
text = [text1,text2,text3,text4,text5]

for index, t in enumerate(text):
    x = t.split('\n')
    counter = 1

    for line in x:
        if(len(line)>0):
            function = line[line.index('&')+1:line.index(',')]
            data[index].append("PAPIEX_START_ARG({},\"{}\");\n".format(str(counter),function))
            data[index].append(line + '\n')
            data[index].append("PAPIEX_STOP_ARG({}); \n".format(str(counter)))
            counter +=1
    data[index].append("return 0; }")

from settings import TSVC_PATH
import os
for index, d in enumerate(data):
    with open(os.path.join(TSVC_PATH,'time_{}'.join(str(index))), 'w') as f:
        for item in d:
            f.write("%s" % item)