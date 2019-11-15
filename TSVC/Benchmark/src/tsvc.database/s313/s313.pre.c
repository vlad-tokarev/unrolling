real_t s313(struct args_t *func_args)
{
   //PIPS generated variable
   int LU_NUB0, LU_IB0, LU_IND0;
   
   //    reductions
   //    dot product
   
   initialise_arrays(__func__);
   gettimeofday(&func_args->t1, (void *) 0);

   real_t dot;
   {
      int nl;
      for(nl = 0; nl <= 499999; nl += 1) {
         dot = (real_t) 0.;
         {
            int i;
loop_s313:            LU_NUB0 = 32000;
            LU_IB0 = 3;
            for(LU_IND0 = 0; LU_IND0 <= LU_IB0-1; LU_IND0 += 1) {
               dot += a[LU_IND0*1+0]*b[LU_IND0*1+0];
l99827:               ;
            }
            for(LU_IND0 = LU_IB0; LU_IND0 <= LU_NUB0-1; LU_IND0 += 7) {
               dot += a[(LU_IND0+0)*1+0]*b[(LU_IND0+0)*1+0];
               dot += a[(LU_IND0+1)*1+0]*b[(LU_IND0+1)*1+0];
               dot += a[(LU_IND0+2)*1+0]*b[(LU_IND0+2)*1+0];
               dot += a[(LU_IND0+3)*1+0]*b[(LU_IND0+3)*1+0];
               dot += a[(LU_IND0+4)*1+0]*b[(LU_IND0+4)*1+0];
               dot += a[(LU_IND0+5)*1+0]*b[(LU_IND0+5)*1+0];
               dot += a[(LU_IND0+6)*1+0]*b[(LU_IND0+6)*1+0];
l99826:               ;
            }
            i = 0+MAX0(LU_NUB0, 0)*1;
         }
         dummy(a, b, c, d, e, aa, bb, cc, dot);
      }
   }

   gettimeofday(&func_args->t2, (void *) 0);
   return dot;
}
