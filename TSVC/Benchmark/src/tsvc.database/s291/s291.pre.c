real_t s291(struct args_t *func_args)
{
   //PIPS generated variable
   int LU_NUB0, LU_IB0, LU_IND0;
   
   //    loop peeling
   //    wrap around variable, 1 level
   
   initialise_arrays(__func__);
   gettimeofday(&func_args->t1, (void *) 0);

   int im1;
   {
      int nl;
      for(nl = 0; nl <= 199999; nl += 1) {
         im1 = 32000-1;
         {
            int i;
loop_s291:            LU_NUB0 = 32000;
            LU_IB0 = 3;
            for(LU_IND0 = 0; LU_IND0 <= LU_IB0-1; LU_IND0 += 1) {
               a[LU_IND0*1+0] = (b[LU_IND0*1+0]+b[im1])*(real_t) .5;
               im1 = LU_IND0*1+0;
l99845:               ;
            }
            for(LU_IND0 = LU_IB0; LU_IND0 <= LU_NUB0-1; LU_IND0 += 7) {
               a[(LU_IND0+0)*1+0] = (b[(LU_IND0+0)*1+0]+b[im1])*(real_t) .5;
               im1 = (LU_IND0+0)*1+0;
               a[(LU_IND0+1)*1+0] = (b[(LU_IND0+1)*1+0]+b[im1])*(real_t) .5;
               im1 = (LU_IND0+1)*1+0;
               a[(LU_IND0+2)*1+0] = (b[(LU_IND0+2)*1+0]+b[im1])*(real_t) .5;
               im1 = (LU_IND0+2)*1+0;
               a[(LU_IND0+3)*1+0] = (b[(LU_IND0+3)*1+0]+b[im1])*(real_t) .5;
               im1 = (LU_IND0+3)*1+0;
               a[(LU_IND0+4)*1+0] = (b[(LU_IND0+4)*1+0]+b[im1])*(real_t) .5;
               im1 = (LU_IND0+4)*1+0;
               a[(LU_IND0+5)*1+0] = (b[(LU_IND0+5)*1+0]+b[im1])*(real_t) .5;
               im1 = (LU_IND0+5)*1+0;
               a[(LU_IND0+6)*1+0] = (b[(LU_IND0+6)*1+0]+b[im1])*(real_t) .5;
               im1 = (LU_IND0+6)*1+0;
l99844:               ;
            }
            i = 0+MAX0(LU_NUB0, 0)*1;
         }
         dummy(a, b, c, d, e, aa, bb, cc, 0.);
      }
   }

   gettimeofday(&func_args->t2, (void *) 0);
   return calc_checksum(__func__);
}
