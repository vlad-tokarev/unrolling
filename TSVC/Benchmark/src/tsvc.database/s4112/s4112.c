# 8717 "tsvc_new.c"
real_t s4112(struct args_t *func_args)
{

//    indirect addressing
//    sparse saxpy
//    gather is required

struct {
int * restrict a;
real_t b;
} *x = func_args->arg_info;
int * restrict ip = x->a;
real_t s = x->b;

initialise_arrays(__func__);
gettimeofday(&func_args->t1, (void *) 0);
{
int nl;

for(nl = 0; nl <= 99999; nl += 1) {
{
int i;
loop_s4112: for(i = 0; i <= 31999; i += 1)
a[i] += b[ip[i]]*s;
}
dummy(a, b, c, d, e, aa, bb, cc, 0.);
}
}

gettimeofday(&func_args->t2, (void *) 0);
return calc_checksum(__func__);
}
