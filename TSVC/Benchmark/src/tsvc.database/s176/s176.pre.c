real_t s176(struct args_t *func_args)
{
   //PIPS generated variable
   int LU_NUB0, LU_IB0, LU_IND0;
   
   //    symbolics
   //    convolution
   
   initialise_arrays(__func__);
   gettimeofday(&func_args->t1, (void *) 0);

   int m = 32000/2;
   {
      int nl;
      for(nl = 0; nl <= 11; nl += 1) {
         {
            int j;
            for(j = 0; j <= 15999; j += 1) {
               int i;
loop_s176:               LU_NUB0 = (m-1-0+1)/1;
               LU_IB0 = MOD(LU_NUB0, 7);
               for(LU_IND0 = 0; LU_IND0 <= LU_IB0-1; LU_IND0 += 1) {
                  a[LU_IND0*1+0] += b[LU_IND0*1+0+m-j-1]*c[j];
l99933:                  ;
               }
               for(LU_IND0 = LU_IB0; LU_IND0 <= LU_NUB0-1; LU_IND0 += 7) {
                  a[(LU_IND0+0)*1+0] += b[(LU_IND0+0)*1+0+m-j-1]*c[j];
                  a[(LU_IND0+1)*1+0] += b[(LU_IND0+1)*1+0+m-j-1]*c[j];
                  a[(LU_IND0+2)*1+0] += b[(LU_IND0+2)*1+0+m-j-1]*c[j];
                  a[(LU_IND0+3)*1+0] += b[(LU_IND0+3)*1+0+m-j-1]*c[j];
                  a[(LU_IND0+4)*1+0] += b[(LU_IND0+4)*1+0+m-j-1]*c[j];
                  a[(LU_IND0+5)*1+0] += b[(LU_IND0+5)*1+0+m-j-1]*c[j];
                  a[(LU_IND0+6)*1+0] += b[(LU_IND0+6)*1+0+m-j-1]*c[j];
l99932:                  ;
               }
               i = 0+MAX0(LU_NUB0, 0)*1;
            }
         }
         dummy(a, b, c, d, e, aa, bb, cc, 0.);
      }
   }

   gettimeofday(&func_args->t2, (void *) 0);
   return calc_checksum(__func__);
}
