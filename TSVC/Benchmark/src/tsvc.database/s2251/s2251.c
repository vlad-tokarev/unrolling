# 6531 "tsvc_new.c"
real_t s2251(struct args_t *func_args)
{

//    scalar and array expansion
//    scalar expansion

initialise_arrays(__func__);
gettimeofday(&func_args->t1, (void *) 0);
{
int nl;

for(nl = 0; nl <= 99999; nl += 1) {
real_t s = (real_t) 0.0;
{
int i;
loop_s2251: for(i = 0; i <= 31999; i += 1) {
a[i] = s*e[i];
s = b[i]+c[i];
b[i] = a[i]+d[i];
}
}
dummy(a, b, c, d, e, aa, bb, cc, 0.);
}
}

gettimeofday(&func_args->t2, (void *) 0);
return calc_checksum(__func__);
}
