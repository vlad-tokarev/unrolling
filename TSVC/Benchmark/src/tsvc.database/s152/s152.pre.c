real_t s152(struct args_t *func_args)
{
   //PIPS generated variable
   int LU_NUB0, LU_IB0, LU_IND0;
   
   //    interprocedural data flow analysis
   //    collecting information from a subroutine
   
   initialise_arrays(__func__);
   gettimeofday(&func_args->t1, (void *) 0);
   {
      int nl;

      for(nl = 0; nl <= 99999; nl += 1) {
         {
            int i;
loop_s152:            LU_NUB0 = 32000;
            LU_IB0 = 3;
            for(LU_IND0 = 0; LU_IND0 <= LU_IB0-1; LU_IND0 += 1) {
               b[LU_IND0*1+0] = d[LU_IND0*1+0]*e[LU_IND0*1+0];
               s152s(a, b, c, LU_IND0*1+0);
l99947:               ;
            }
            for(LU_IND0 = LU_IB0; LU_IND0 <= LU_NUB0-1; LU_IND0 += 7) {
               b[(LU_IND0+0)*1+0] = d[(LU_IND0+0)*1+0]*e[(LU_IND0+0)*1+0];
               s152s(a, b, c, (LU_IND0+0)*1+0);
               b[(LU_IND0+1)*1+0] = d[(LU_IND0+1)*1+0]*e[(LU_IND0+1)*1+0];
               s152s(a, b, c, (LU_IND0+1)*1+0);
               b[(LU_IND0+2)*1+0] = d[(LU_IND0+2)*1+0]*e[(LU_IND0+2)*1+0];
               s152s(a, b, c, (LU_IND0+2)*1+0);
               b[(LU_IND0+3)*1+0] = d[(LU_IND0+3)*1+0]*e[(LU_IND0+3)*1+0];
               s152s(a, b, c, (LU_IND0+3)*1+0);
               b[(LU_IND0+4)*1+0] = d[(LU_IND0+4)*1+0]*e[(LU_IND0+4)*1+0];
               s152s(a, b, c, (LU_IND0+4)*1+0);
               b[(LU_IND0+5)*1+0] = d[(LU_IND0+5)*1+0]*e[(LU_IND0+5)*1+0];
               s152s(a, b, c, (LU_IND0+5)*1+0);
               b[(LU_IND0+6)*1+0] = d[(LU_IND0+6)*1+0]*e[(LU_IND0+6)*1+0];
               s152s(a, b, c, (LU_IND0+6)*1+0);
l99946:               ;
            }
            i = 0+MAX0(LU_NUB0, 0)*1;
         }
         dummy(a, b, c, d, e, aa, bb, cc, 0.);
      }
   }

   gettimeofday(&func_args->t2, (void *) 0);
   return calc_checksum(__func__);
}
