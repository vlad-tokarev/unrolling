# 8524 "tsvc_new.c"
real_t s451(struct args_t *func_args)
{

//    intrinsic functions
//    intrinsics

initialise_arrays(__func__);
gettimeofday(&func_args->t1, (void *) 0);
{
int nl;

for(nl = 0; nl <= 19999; nl += 1) {
{
int i;
loop_s451: for(i = 0; i <= 31999; i += 1)
a[i] = sinf(b[i])+cosf(c[i]);
}
dummy(a, b, c, d, e, aa, bb, cc, 0.);
}
}

gettimeofday(&func_args->t2, (void *) 0);
return calc_checksum(__func__);
}
