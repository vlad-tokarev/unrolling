real_t s132(struct args_t *func_args)
{
   //PIPS generated variable
   int LU_NUB0, LU_IB0, LU_IND0;
   //    global data flow analysis
   //    loop with multiple dimension ambiguous subscripts
   
   initialise_arrays(__func__);
   gettimeofday(&func_args->t1, (void *) 0);

   int m = 0;
   int j = m;
   int k = m+1;
   {
      int nl;
      for(nl = 0; nl <= 39999999; nl += 1) {
         {
            int i;
loop_s132:            LU_NUB0 = 255;
            LU_IB0 = 3;
            for(LU_IND0 = 0; LU_IND0 <= LU_IB0-1; LU_IND0 += 1) {
               aa[j][LU_IND0*1+1] = aa[k][LU_IND0*1+1-1]+b[LU_IND0*1+1]*c[1];
l99953:               ;
            }
            for(LU_IND0 = LU_IB0; LU_IND0 <= LU_NUB0-1; LU_IND0 += 7) {
               aa[j][(LU_IND0+0)*1+1] = aa[k][(LU_IND0+0)*1+1-1]+b[(LU_IND0+0)*1+1]*c[1];
               aa[j][(LU_IND0+1)*1+1] = aa[k][(LU_IND0+1)*1+1-1]+b[(LU_IND0+1)*1+1]*c[1];
               aa[j][(LU_IND0+2)*1+1] = aa[k][(LU_IND0+2)*1+1-1]+b[(LU_IND0+2)*1+1]*c[1];
               aa[j][(LU_IND0+3)*1+1] = aa[k][(LU_IND0+3)*1+1-1]+b[(LU_IND0+3)*1+1]*c[1];
               aa[j][(LU_IND0+4)*1+1] = aa[k][(LU_IND0+4)*1+1-1]+b[(LU_IND0+4)*1+1]*c[1];
               aa[j][(LU_IND0+5)*1+1] = aa[k][(LU_IND0+5)*1+1-1]+b[(LU_IND0+5)*1+1]*c[1];
               aa[j][(LU_IND0+6)*1+1] = aa[k][(LU_IND0+6)*1+1-1]+b[(LU_IND0+6)*1+1]*c[1];
l99952:               ;
            }
            i = 1+MAX0(LU_NUB0, 0)*1;
         }
         dummy(a, b, c, d, e, aa, bb, cc, 0.);
      }
   }

   gettimeofday(&func_args->t2, (void *) 0);
   return calc_checksum(__func__);
}
