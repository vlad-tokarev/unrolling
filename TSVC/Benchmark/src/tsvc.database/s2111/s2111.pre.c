real_t s2111(struct args_t *func_args)
{
   //PIPS generated variable
   int LU_NUB0, LU_IB0, LU_IND0;
   
   //    wavefronts, it will make jump in data access
   
   initialise_arrays(__func__);
   gettimeofday(&func_args->t1, (void *) 0);
   {
      int nl;

      for(nl = 0; nl <= 38999; nl += 1) {
         {
            int j;
            for(j = 1; j <= 255; j += 1) {
               int i;
loop_s2111:               LU_NUB0 = 255;
               LU_IB0 = 3;
               for(LU_IND0 = 0; LU_IND0 <= LU_IB0-1; LU_IND0 += 1) {
                  aa[j][LU_IND0*1+1] = (aa[j][LU_IND0*1+1-1]+aa[j-1][LU_IND0*1+1])/1.9;
l99835:                  ;
               }
               for(LU_IND0 = LU_IB0; LU_IND0 <= LU_NUB0-1; LU_IND0 += 7) {
                  aa[j][(LU_IND0+0)*1+1] = (aa[j][(LU_IND0+0)*1+1-1]+aa[j-1][(LU_IND0+0)*1+1])/1.9;
                  aa[j][(LU_IND0+1)*1+1] = (aa[j][(LU_IND0+1)*1+1-1]+aa[j-1][(LU_IND0+1)*1+1])/1.9;
                  aa[j][(LU_IND0+2)*1+1] = (aa[j][(LU_IND0+2)*1+1-1]+aa[j-1][(LU_IND0+2)*1+1])/1.9;
                  aa[j][(LU_IND0+3)*1+1] = (aa[j][(LU_IND0+3)*1+1-1]+aa[j-1][(LU_IND0+3)*1+1])/1.9;
                  aa[j][(LU_IND0+4)*1+1] = (aa[j][(LU_IND0+4)*1+1-1]+aa[j-1][(LU_IND0+4)*1+1])/1.9;
                  aa[j][(LU_IND0+5)*1+1] = (aa[j][(LU_IND0+5)*1+1-1]+aa[j-1][(LU_IND0+5)*1+1])/1.9;
                  aa[j][(LU_IND0+6)*1+1] = (aa[j][(LU_IND0+6)*1+1-1]+aa[j-1][(LU_IND0+6)*1+1])/1.9;
l99834:                  ;
               }
               i = 1+MAX0(LU_NUB0, 0)*1;
            }
         }
         dummy(a, b, c, d, e, aa, bb, cc, 0.);
      }
   }

   gettimeofday(&func_args->t2, (void *) 0);
   return calc_checksum(__func__);
}
