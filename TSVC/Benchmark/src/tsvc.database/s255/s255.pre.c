real_t s255(struct args_t *func_args)
{
   //PIPS generated variable
   int LU_NUB0, LU_IB0, LU_IND0;
   
   //    scalar and array expansion
   //    carry around variables, 2 levels
   
   initialise_arrays(__func__);
   gettimeofday(&func_args->t1, (void *) 0);

   real_t x, y;
   {
      int nl;
      for(nl = 0; nl <= 99999; nl += 1) {
         x = b[32000-1];
         y = b[32000-2];
         {
            int i;
loop_s255:            LU_NUB0 = 32000;
            LU_IB0 = 3;
            for(LU_IND0 = 0; LU_IND0 <= LU_IB0-1; LU_IND0 += 1) {
               a[LU_IND0*1+0] = (b[LU_IND0*1+0]+x+y)*(real_t) .333;
               y = x;
               x = b[LU_IND0*1+0];
l99881:               ;
            }
            for(LU_IND0 = LU_IB0; LU_IND0 <= LU_NUB0-1; LU_IND0 += 7) {
               a[(LU_IND0+0)*1+0] = (b[(LU_IND0+0)*1+0]+x+y)*(real_t) .333;
               y = x;
               x = b[(LU_IND0+0)*1+0];
               a[(LU_IND0+1)*1+0] = (b[(LU_IND0+1)*1+0]+x+y)*(real_t) .333;
               y = x;
               x = b[(LU_IND0+1)*1+0];
               a[(LU_IND0+2)*1+0] = (b[(LU_IND0+2)*1+0]+x+y)*(real_t) .333;
               y = x;
               x = b[(LU_IND0+2)*1+0];
               a[(LU_IND0+3)*1+0] = (b[(LU_IND0+3)*1+0]+x+y)*(real_t) .333;
               y = x;
               x = b[(LU_IND0+3)*1+0];
               a[(LU_IND0+4)*1+0] = (b[(LU_IND0+4)*1+0]+x+y)*(real_t) .333;
               y = x;
               x = b[(LU_IND0+4)*1+0];
               a[(LU_IND0+5)*1+0] = (b[(LU_IND0+5)*1+0]+x+y)*(real_t) .333;
               y = x;
               x = b[(LU_IND0+5)*1+0];
               a[(LU_IND0+6)*1+0] = (b[(LU_IND0+6)*1+0]+x+y)*(real_t) .333;
               y = x;
               x = b[(LU_IND0+6)*1+0];
l99880:               ;
            }
            i = 0+MAX0(LU_NUB0, 0)*1;
         }
         dummy(a, b, c, d, e, aa, bb, cc, 0.);
      }
   }

   gettimeofday(&func_args->t2, (void *) 0);
   return calc_checksum(__func__);
}
