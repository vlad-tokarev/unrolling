# 6109 "tsvc_new.c"
real_t s222(struct args_t *func_args)
{

//    loop distribution
//    partial loop vectorizatio recurrence in middle

initialise_arrays(__func__);
gettimeofday(&func_args->t1, (void *) 0);
{
int nl;

for(nl = 0; nl <= 49999; nl += 1) {
{
int i;
loop_s222: for(i = 1; i <= 31999; i += 1) {
a[i] += b[i]*c[i];
e[i] = e[i-1]*e[i-1];
a[i] -= b[i]*c[i];
}
}
dummy(a, b, c, d, e, aa, bb, cc, 0.);
}
}

gettimeofday(&func_args->t2, (void *) 0);
return calc_checksum(__func__);
}
