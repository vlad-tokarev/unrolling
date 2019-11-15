real_t s231(struct args_t *func_args)
{
   //PIPS generated variable
   int LU_NUB0, LU_IB0, LU_IND0;
   //    loop interchange
   //    loop with data dependency
   
   initialise_arrays(__func__);
   gettimeofday(&func_args->t1, (void *) 0);
   {
      int nl;

      for(nl = 0; nl <= 38999; nl += 1) {
         {
            int i;
            for(i = 0; i <= 255; i += 1) {
               int j;
loop_s231:               LU_NUB0 = 255;
               LU_IB0 = 3;
               for(LU_IND0 = 0; LU_IND0 <= LU_IB0-1; LU_IND0 += 1) {
                  aa[LU_IND0*1+1][i] = aa[LU_IND0*1+1-1][i]+bb[LU_IND0*1+1][i];
l99919:                  ;
               }
               for(LU_IND0 = LU_IB0; LU_IND0 <= LU_NUB0-1; LU_IND0 += 7) {
                  aa[(LU_IND0+0)*1+1][i] = aa[(LU_IND0+0)*1+1-1][i]+bb[(LU_IND0+0)*1+1][i];
                  aa[(LU_IND0+1)*1+1][i] = aa[(LU_IND0+1)*1+1-1][i]+bb[(LU_IND0+1)*1+1][i];
                  aa[(LU_IND0+2)*1+1][i] = aa[(LU_IND0+2)*1+1-1][i]+bb[(LU_IND0+2)*1+1][i];
                  aa[(LU_IND0+3)*1+1][i] = aa[(LU_IND0+3)*1+1-1][i]+bb[(LU_IND0+3)*1+1][i];
                  aa[(LU_IND0+4)*1+1][i] = aa[(LU_IND0+4)*1+1-1][i]+bb[(LU_IND0+4)*1+1][i];
                  aa[(LU_IND0+5)*1+1][i] = aa[(LU_IND0+5)*1+1-1][i]+bb[(LU_IND0+5)*1+1][i];
                  aa[(LU_IND0+6)*1+1][i] = aa[(LU_IND0+6)*1+1-1][i]+bb[(LU_IND0+6)*1+1][i];
l99918:                  ;
               }
               j = 1+MAX0(LU_NUB0, 0)*1;
            }
         }
         dummy(a, b, c, d, e, aa, bb, cc, 0.);
      }
   }

   gettimeofday(&func_args->t2, (void *) 0);
   return calc_checksum(__func__);
}
