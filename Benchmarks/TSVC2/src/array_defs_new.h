#ifndef TSVC_ARRAY_HDR
#define TSVC_ARRAY_HDR

// Arrays used by TSVC and common.c

#define ARRAY_ALIGNMENT 64

extern __attribute__((aligned(ARRAY_ALIGNMENT))) real_t flat_2d_array[LEN_2D*LEN_2D];
extern __attribute__((aligned(ARRAY_ALIGNMENT))) real_t flat_3d_array[LEN_3D*LEN_3D*LEN_3D];

extern __attribute__((aligned(ARRAY_ALIGNMENT))) real_t x[iterations][LEN_1D];

extern __attribute__((aligned(ARRAY_ALIGNMENT))) real_t a[LEN_2D][LEN_2D],b[LEN_2D][LEN_2D],c[LEN_2D][LEN_2D],d[LEN_2D][LEN_2D],e[LEN_2D][LEN_2D],
                                   aa[LEN_3D][LEN_3D][LEN_3D],bb[LEN_3D][LEN_3D][LEN_3D],cc[LEN_3D][LEN_3D][LEN_3D],tt[LEN_3D][LEN_3D][LEN_3D];

extern __attribute__((aligned(ARRAY_ALIGNMENT))) int indx[LEN_2D][LEN_2D];

extern real_t* __restrict__ xx;
extern real_t* yy;

#endif
