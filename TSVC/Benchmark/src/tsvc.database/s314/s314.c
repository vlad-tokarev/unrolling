# 7560 "tsvc_new.c"
real_t s314(struct args_t *func_args)
{

//    reductions
//    if to max reduction

initialise_arrays(__func__);
gettimeofday(&func_args->t1, (void *) 0);

real_t x;
{
int nl;
for(nl = 0; nl <= 499999; nl += 1) {
x = a[0];
{
int i;
loop_s314: for(i = 0; i <= 31999; i += 1)
if (a[i]>x)
x = a[i];
}
dummy(a, b, c, d, e, aa, bb, cc, x);
}
}

gettimeofday(&func_args->t2, (void *) 0);
return x;
}
