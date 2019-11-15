real_t s292(struct args_t *func_args)
{
   //PIPS generated variable
   int LU_NUB0, LU_IB0, LU_IND0;
   
   //    loop peeling
   //    wrap around variable, 2 levels
   //    similar to S291
   
   initialise_arrays(__func__);
   gettimeofday(&func_args->t1, (void *) 0);

   int im1, im2;
   {
      int nl;
      for(nl = 0; nl <= 99999; nl += 1) {
         im1 = 32000-1;
         im2 = 32000-2;
         {
            int i;
loop_s292:            LU_NUB0 = 32000;
            LU_IB0 = 3;
            for(LU_IND0 = 0; LU_IND0 <= LU_IB0-1; LU_IND0 += 1) {
               a[LU_IND0*1+0] = (b[LU_IND0*1+0]+b[im1]+b[im2])*(real_t) .333;
               im2 = im1;
               im1 = LU_IND0*1+0;
l99843:               ;
            }
            for(LU_IND0 = LU_IB0; LU_IND0 <= LU_NUB0-1; LU_IND0 += 7) {
               a[(LU_IND0+0)*1+0] = (b[(LU_IND0+0)*1+0]+b[im1]+b[im2])*(real_t) .333;
               im2 = im1;
               im1 = (LU_IND0+0)*1+0;
               a[(LU_IND0+1)*1+0] = (b[(LU_IND0+1)*1+0]+b[im1]+b[im2])*(real_t) .333;
               im2 = im1;
               im1 = (LU_IND0+1)*1+0;
               a[(LU_IND0+2)*1+0] = (b[(LU_IND0+2)*1+0]+b[im1]+b[im2])*(real_t) .333;
               im2 = im1;
               im1 = (LU_IND0+2)*1+0;
               a[(LU_IND0+3)*1+0] = (b[(LU_IND0+3)*1+0]+b[im1]+b[im2])*(real_t) .333;
               im2 = im1;
               im1 = (LU_IND0+3)*1+0;
               a[(LU_IND0+4)*1+0] = (b[(LU_IND0+4)*1+0]+b[im1]+b[im2])*(real_t) .333;
               im2 = im1;
               im1 = (LU_IND0+4)*1+0;
               a[(LU_IND0+5)*1+0] = (b[(LU_IND0+5)*1+0]+b[im1]+b[im2])*(real_t) .333;
               im2 = im1;
               im1 = (LU_IND0+5)*1+0;
               a[(LU_IND0+6)*1+0] = (b[(LU_IND0+6)*1+0]+b[im1]+b[im2])*(real_t) .333;
               im2 = im1;
               im1 = (LU_IND0+6)*1+0;
l99842:               ;
            }
            i = 0+MAX0(LU_NUB0, 0)*1;
         }
         dummy(a, b, c, d, e, aa, bb, cc, 0.);
      }
   }

   gettimeofday(&func_args->t2, (void *) 0);
   return calc_checksum(__func__);
}
