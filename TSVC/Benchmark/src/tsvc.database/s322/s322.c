# 7929 "tsvc_new.c"
real_t s322(struct args_t *func_args)
{

//    recurrences
//    second order linear recurrence

initialise_arrays(__func__);
gettimeofday(&func_args->t1, (void *) 0);
{
int nl;

for(nl = 0; nl <= 49999; nl += 1) {
{
int i;
loop_s322: for(i = 2; i <= 31999; i += 1)
a[i] = a[i]+a[i-1]*b[i]+a[i-2]*c[i];
}
dummy(a, b, c, d, e, aa, bb, cc, 0.);
}
}

gettimeofday(&func_args->t2, (void *) 0);
return calc_checksum(__func__);
}
