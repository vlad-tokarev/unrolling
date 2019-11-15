real_t s453(struct args_t *func_args)
{
   
   //    induction varibale recognition
   
   real_t s;
   //PIPS generated variable
   int LU_NUB0, LU_IB0, LU_IND0;

   initialise_arrays(__func__);
   gettimeofday(&func_args->t1, (void *) 0);
   {
      int nl;

      for(nl = 0; nl <= 199999; nl += 1) {
         s = 0.;
         {
            int i;
loop_s453:            LU_NUB0 = 32000;
            LU_IB0 = 3;
            for(LU_IND0 = 0; LU_IND0 <= LU_IB0-1; LU_IND0 += 1) {
               s += (real_t) 2.;
               a[LU_IND0*1+0] = s*b[LU_IND0*1+0];
l99765:               ;
            }
            for(LU_IND0 = LU_IB0; LU_IND0 <= LU_NUB0-1; LU_IND0 += 7) {
               s += (real_t) 2.;
               a[(LU_IND0+0)*1+0] = s*b[(LU_IND0+0)*1+0];
               s += (real_t) 2.;
               a[(LU_IND0+1)*1+0] = s*b[(LU_IND0+1)*1+0];
               s += (real_t) 2.;
               a[(LU_IND0+2)*1+0] = s*b[(LU_IND0+2)*1+0];
               s += (real_t) 2.;
               a[(LU_IND0+3)*1+0] = s*b[(LU_IND0+3)*1+0];
               s += (real_t) 2.;
               a[(LU_IND0+4)*1+0] = s*b[(LU_IND0+4)*1+0];
               s += (real_t) 2.;
               a[(LU_IND0+5)*1+0] = s*b[(LU_IND0+5)*1+0];
               s += (real_t) 2.;
               a[(LU_IND0+6)*1+0] = s*b[(LU_IND0+6)*1+0];
l99764:               ;
            }
            i = 0+MAX0(LU_NUB0, 0)*1;
         }
         dummy(a, b, c, d, e, aa, bb, cc, 0.);
      }
   }

   gettimeofday(&func_args->t2, (void *) 0);
   return calc_checksum(__func__);
}
