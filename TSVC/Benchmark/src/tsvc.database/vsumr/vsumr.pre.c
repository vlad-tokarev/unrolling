real_t vsumr(struct args_t *func_args)
{
   //PIPS generated variable
   int LU_NUB0, LU_IB0, LU_IND0;
   
   //    control loops
   //    vector sum reduction
   
   initialise_arrays(__func__);
   gettimeofday(&func_args->t1, (void *) 0);

   real_t sum;
   {
      int nl;
      for(nl = 0; nl <= 999999; nl += 1) {
         sum = 0.;
         {
            int i;
loop_vsumr:            LU_NUB0 = 32000;
            LU_IB0 = 3;
            for(LU_IND0 = 0; LU_IND0 <= LU_IB0-1; LU_IND0 += 1) {
               sum += a[LU_IND0*1+0];
l99723:               ;
            }
            for(LU_IND0 = LU_IB0; LU_IND0 <= LU_NUB0-1; LU_IND0 += 7) {
               sum += a[(LU_IND0+0)*1+0];
               sum += a[(LU_IND0+1)*1+0];
               sum += a[(LU_IND0+2)*1+0];
               sum += a[(LU_IND0+3)*1+0];
               sum += a[(LU_IND0+4)*1+0];
               sum += a[(LU_IND0+5)*1+0];
               sum += a[(LU_IND0+6)*1+0];
l99722:               ;
            }
            i = 0+MAX0(LU_NUB0, 0)*1;
         }
         dummy(a, b, c, d, e, aa, bb, cc, sum);
      }
   }

   gettimeofday(&func_args->t2, (void *) 0);
   return sum;
}
