# 6216 "tsvc_new.c"
real_t s233(struct args_t *func_args)
{

//    loop interchange
//    interchanging with one of two inner loops

initialise_arrays(__func__);
gettimeofday(&func_args->t1, (void *) 0);
{
int nl;

for(nl = 0; nl <= 38999; nl += 1) {
{
int i;
for(i = 1; i <= 255; i += 1) {
{
int j;
for(j = 1; j <= 255; j += 1)
aa[j][i] = aa[j-1][i]+cc[j][i];
}
{
int j;
loop_s233: for(j = 1; j <= 255; j += 1)
bb[j][i] = bb[j][i-1]+cc[j][i];
}
}
}
dummy(a, b, c, d, e, aa, bb, cc, 0.);
}
}

gettimeofday(&func_args->t2, (void *) 0);
return calc_checksum(__func__);
}
