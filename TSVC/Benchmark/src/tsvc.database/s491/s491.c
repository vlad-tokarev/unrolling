# 8690 "tsvc_new.c"
real_t s491(struct args_t *func_args)
{

//    vector semantics
//    indirect addressing on lhs, store in sequence
//    scatter is required

int * restrict ip = func_args->arg_info;

initialise_arrays(__func__);
gettimeofday(&func_args->t1, (void *) 0);
{
int nl;

for(nl = 0; nl <= 99999; nl += 1) {
{
int i;
loop_s491: for(i = 0; i <= 31999; i += 1)
a[ip[i]] = b[i]+c[i]*d[i];
}
dummy(a, b, c, d, e, aa, bb, cc, 0.);
}
}

gettimeofday(&func_args->t2, (void *) 0);
return calc_checksum(__func__);
}
