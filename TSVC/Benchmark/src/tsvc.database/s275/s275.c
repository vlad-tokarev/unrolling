# 6930 "tsvc_new.c"
real_t s275(struct args_t *func_args)
{

//    control flow
//    if around inner loop, interchanging needed

initialise_arrays(__func__);
gettimeofday(&func_args->t1, (void *) 0);
{
int nl;

for(nl = 0; nl <= 3899; nl += 1) {
{
int i;
for(i = 0; i <= 255; i += 1)
if (aa[0][i]>(real_t) 0.) {
int j;
loop_s275: for(j = 1; j <= 255; j += 1)
aa[j][i] = aa[j-1][i]+bb[j][i]*cc[j][i];
}
}
dummy(a, b, c, d, e, aa, bb, cc, 0.);
}
}

gettimeofday(&func_args->t2, (void *) 0);
return calc_checksum(__func__);
}
