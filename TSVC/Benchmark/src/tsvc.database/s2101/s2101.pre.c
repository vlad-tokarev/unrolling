real_t s2101(struct args_t *func_args)
{
   //PIPS generated variable
   int LU_NUB0, LU_IB0, LU_IND0;
   
   //    diagonals
   //    main diagonal calculation
   //    jump in data access
   
   initialise_arrays(__func__);
   gettimeofday(&func_args->t1, (void *) 0);
   {
      int nl;

      for(nl = 0; nl <= 999999; nl += 1) {
         {
            int i;
loop_s2101:            LU_NUB0 = 256;
            LU_IB0 = 4;
            for(LU_IND0 = 0; LU_IND0 <= LU_IB0-1; LU_IND0 += 1) {
               aa[LU_IND0*1+0][LU_IND0*1+0] += bb[LU_IND0*1+0][LU_IND0*1+0]*cc[LU_IND0*1+0][LU_IND0*1+0];
l99839:               ;
            }
            for(LU_IND0 = LU_IB0; LU_IND0 <= LU_NUB0-1; LU_IND0 += 7) {
               aa[(LU_IND0+0)*1+0][(LU_IND0+0)*1+0] += bb[(LU_IND0+0)*1+0][(LU_IND0+0)*1+0]*cc[(LU_IND0+0)*1+0][(LU_IND0+0)*1+0];
               aa[(LU_IND0+1)*1+0][(LU_IND0+1)*1+0] += bb[(LU_IND0+1)*1+0][(LU_IND0+1)*1+0]*cc[(LU_IND0+1)*1+0][(LU_IND0+1)*1+0];
               aa[(LU_IND0+2)*1+0][(LU_IND0+2)*1+0] += bb[(LU_IND0+2)*1+0][(LU_IND0+2)*1+0]*cc[(LU_IND0+2)*1+0][(LU_IND0+2)*1+0];
               aa[(LU_IND0+3)*1+0][(LU_IND0+3)*1+0] += bb[(LU_IND0+3)*1+0][(LU_IND0+3)*1+0]*cc[(LU_IND0+3)*1+0][(LU_IND0+3)*1+0];
               aa[(LU_IND0+4)*1+0][(LU_IND0+4)*1+0] += bb[(LU_IND0+4)*1+0][(LU_IND0+4)*1+0]*cc[(LU_IND0+4)*1+0][(LU_IND0+4)*1+0];
               aa[(LU_IND0+5)*1+0][(LU_IND0+5)*1+0] += bb[(LU_IND0+5)*1+0][(LU_IND0+5)*1+0]*cc[(LU_IND0+5)*1+0][(LU_IND0+5)*1+0];
               aa[(LU_IND0+6)*1+0][(LU_IND0+6)*1+0] += bb[(LU_IND0+6)*1+0][(LU_IND0+6)*1+0]*cc[(LU_IND0+6)*1+0][(LU_IND0+6)*1+0];
l99838:               ;
            }
            i = 0+MAX0(LU_NUB0, 0)*1;
         }
         dummy(a, b, c, d, e, aa, bb, cc, 0.);
      }
   }

   gettimeofday(&func_args->t2, (void *) 0);
   return calc_checksum(__func__);
}
