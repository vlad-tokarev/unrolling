
/*
 * This is an executable test containing a number of loops to measure
 * the performance of a compiler. Arrays' length is LEN_1D by default
 * and if you want a different array length, you should replace every
 * LEN_1D by your desired number which must be a multiple of 40. If you
 * want to increase the number of loop calls to have a longer run time
 * you have to manipulate the constant value iterations. There is a dummy
 * function called in each loop to make all computations appear required.
 * The time to execute this function is included in the time measurement
 * for the output but it is neglectable.
 *
 *  The output includes three columns:
 *    Loop:        The name of the loop
 *    Time(Sec):     The time in seconds to run the loop
 *    Checksum:    The checksum calculated when the test has run
 *
 * In this version of the codelets arrays are static type.
 *
 * All functions/loops are taken from "TEST SUITE FOR VECTORIZING COMPILERS"
 * by David Callahan, Jack Dongarra and David Levine except those whose
 * functions' name have 4 digits.
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#include "common_new.h"
#include "array_defs_new.h"

// array definitions
__attribute__((aligned(ARRAY_ALIGNMENT))) real_t flat_2d_array[LEN_2D*LEN_2D];

__attribute__((aligned(ARRAY_ALIGNMENT))) real_t x[LEN_2D][LEN_1D];

__attribute__((aligned(ARRAY_ALIGNMENT))) real_t a[LEN_2D][LEN_2D],b[LEN_2D][LEN_2D],c[LEN_2D][LEN_2D],d[LEN_2D][LEN_2D],e[LEN_2D][LEN_2D],
                                   aa[LEN_3D][LEN_3D][LEN_3D],bb[LEN_3D][LEN_3D][LEN_3D],cc[LEN_3D][LEN_3D][LEN_3D],tt[LEN_3D][LEN_3D][LEN_3D];

__attribute__((aligned(ARRAY_ALIGNMENT))) int indx[LEN_2D][LEN_2D];

real_t* __restrict__ xx;
real_t* yy;

real_t s000(struct args_t * func_args)
{

//    linear dependence testing
//    no dependence - vectorizable

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = b[nl-1][i] + 1;
        }
        dummy((real_t*)a, (real_t*)b, (real_t*)c, (real_t*)d, (real_t*)e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.1
real_t s111(struct args_t * func_args)
{

//    linear dependence testing
//    no dependence - vectorizable

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_1D; i += 2) {
            a[nl][i] = a[nl-1][i - 1] + b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1111(struct args_t * func_args)
{

//    no dependence - vectorizable
//    jump in data access

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D/2; i++) {
            a[nl][2*i] = c[nl-1][i] * b[nl-1][i] + d[nl-1][i] * b[nl-1][i] + c[nl-1][i] * c[nl-1][i] + d[nl-1][i] * b[nl-1][i] + d[nl-1][i] * c[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.1

real_t s112(struct args_t * func_args)
{

//    linear dependence testing
//    loop reversal

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = LEN_1D - 2; i >= 0; i--) {
            a[nl][i+1] = a[nl-1][i] + b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1112(struct args_t * func_args)
{

//    linear dependence testing
//    loop reversal

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = LEN_1D - 1; i >= 0; i--) {
            a[nl][i] = b[nl-1][i] + (real_t) 1.;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.1

real_t s113(struct args_t * func_args)
{

//    linear dependence testing
//    a(i)=a(1) but no actual dependence cycle

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_1D; i++) {
            a[nl][i] = a[nl-1][0] + b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1113(struct args_t * func_args)
{

//    linear dependence testing
//    one iteration dependency on a(LEN_1D/2) but still vectorizable

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = a[nl-1][LEN_1D/2] + b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.1

real_t s114(struct args_t * func_args)
{

//    linear dependence testing
//    transpose vectorization
//    Jump in data access - not vectorizable

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_2D; i++) {
            for (int j = 0; j < i; j++) {
                aa[nl][i][j] = aa[nl-1][j][i] + bb[nl-1][i][j];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.1

real_t s115(struct args_t * func_args)
{

//    linear dependence testing
//    triangular saxpy loop

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int j = 0; j < LEN_2D; j++) {
            for (int i = j+1; i < LEN_2D; i++) {
                a[nl][i] -= aa[nl-1][j][i] * a[nl-1][j];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1115(struct args_t * func_args)
{

//    linear dependence testing
//    triangular saxpy loop +

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_2D; i++) {
            for (int j = 0; j < LEN_2D; j++) {
                aa[nl][i][j] = aa[nl-1][i][j]*cc[j][i] + bb[nl-1][i][j];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.1

real_t s116(struct args_t * func_args)
{

//    linear dependence testing

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D - 5; i += 5) {
            a[nl][i] = a[nl-1][i + 1] * a[nl-1][i];
            a[nl][i + 1] = a[nl-1][i + 2] * a[nl-1][i + 1];
            a[nl][i + 2] = a[nl-1][i + 3] * a[nl-1][i + 2];
            a[nl][i + 3] = a[nl-1][i + 4] * a[nl-1][i + 3];
            a[nl][i + 4] = a[nl-1][i + 5] * a[nl-1][i + 4];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.1

real_t s118(struct args_t * func_args)
{

//    linear dependence testing
//    potential dot product recursion

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_2D; i++) {
            for (int j = 0; j <= i - 1; j++) {
                a[nl][i] += bb[nl-1][j][i] * a[nl-1][i-j-1];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.1

real_t s119(struct args_t * func_args)
{

//    linear dependence testing
//    no dependence - vectorizable

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_2D; i++) {
            for (int j = 1; j < LEN_2D; j++) {
                aa[nl][i][j] = aa[nl-1][i-1][j-1] + bb[nl-1][i][j];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1119(struct args_t * func_args)
{

//    linear dependence testing
//    no dependence - vectorizable

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_2D; i++) {
            for (int j = 0; j < LEN_2D; j++) {
                aa[nl][i][j] = aa[nl-1][i-1][j] + bb[nl-1][i][j];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.2

real_t s121(struct args_t * func_args)
{

//    induction variable recognition
//    loop with possible ambiguity because of scalar store

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int j;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D-1; i++) {
            j = i + 1;
            a[nl][i] = a[nl-1][j] + b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.2

real_t s122(struct args_t * func_args)
{

//    induction variable recognition
//    variable lower and upper bound, and stride
//    reverse data access and jump in data access

    struct{int a;int b;} * x = func_args->arg_info;
    int n1 = x->a;
    int n3 = x->b;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int j, k;
    for (int nl = 1; nl < LEN_3D nl++) {
        j = 1;
        k = 0;
        for (int i = n1-1; i < LEN_1D; i += n3) {
            k += j;
            a[nl][i] += b[nl-1][LEN_1D - k];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.2

real_t s123(struct args_t * func_args)
{

//    induction variable recognition
//    induction variable under an if
//    not vectorizable, the condition cannot be speculated

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int j;
    for (int nl = 1; nl < LEN_3D nl++) {
        j = -1;
        for (int i = 0; i < (LEN_1D/2); i++) {
            j++;
            a[nl][j] = b[nl-1][i] + d[nl-1][i] * e[nl-1][i];
            if (c[nl-1][i] > (real_t)0.) {
                j++;
                a[nl][j] = c[nl-1][i] + d[nl-1][i] * e[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.2

real_t s124(struct args_t * func_args)
{

//    induction variable recognition
//    induction variable under both sides of if (same value)

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int j;
    for (int nl = 1; nl < LEN_3D nl++) {
        j = -1;
        for (int i = 0; i < LEN_1D; i++) {
            if (b[nl-1][i] > (real_t)0.) {
                j++;
                a[nl][j] = b[nl-1][i] + d[nl-1][i] * e[nl-1][i];
            } else {
                j++;
                a[nl][j] = c[nl-1][i] + d[nl-1][i] * e[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.2
real_t s125(struct args_t * func_args)
{

//    induction variable recognition
//    induction variable in two loops; collapsing possible

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int k;
    for (int nl = 1; nl < LEN_3D nl++) {
        k = -1;
        for (int i = 0; i < LEN_2D; i++) {
            for (int j = 0; j < LEN_2D; j++) {
                k++;
                flat_2d_array[nl][k] = aa[nl-1][i][j] + bb[nl-1][i][j] * cc[nl-1][i][j];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.2
real_t s126(struct args_t * func_args)
{

//    induction variable recognition
//    induction variable in two loops; recurrence in inner loop

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int k;
    for (int nl = 1; nl < LEN_3D nl++) {
        k = 1;
        for (int i = 0; i < LEN_2D; i++) {
            for (int j = 1; j < LEN_2D; j++) {
                bb[nl][j][i] = bb[nl-1][j-1][i] + flat_2d_array[nl-1][k-1] * cc[nl-1][j][i];
                ++k;
            }
            ++k;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.2

real_t s127(struct args_t * func_args)
{

//    induction variable recognition
//    induction variable with multiple increments

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int j;
    for (int nl = 1; nl < LEN_3D nl++) {
        j = -1;
        for (int i = 0; i < LEN_1D/2; i++) {
            j++;
            a[nl][j] = b[nl-1][i] + c[nl-1][i] * d[nl-1][i];
            j++;
            a[nl][j] = b[nl-1][i] + d[nl-1][i] * e[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.2

real_t s128(struct args_t * func_args)
{

//    induction variables
//    coupled induction variables
//    jump in data access

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int j, k;
    for (int nl = 1; nl < LEN_3D nl++) {
        j = -1;
        for (int i = 0; i < LEN_1D/2; i++) {
            k = j + 1;
            a[nl][i] = b[nl-1][k] - d[nl-1][i];
            j = k + 1;
            b[nl][k] = a[nl-1][i] + c[nl-1][k];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 1.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.3

real_t s131(struct args_t * func_args)
{
//    global data flow analysis
//    forward substitution

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int m  = 1;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D - 1; i++) {
            a[nl][i] = a[nl-1][i + m] + b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.3

real_t s132(struct args_t * func_args)
{
//    global data flow analysis
//    loop with multiple dimension ambiguous subscripts

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int m = 0;
    int j = m;
    int k = m+1;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i= 1; i < LEN_2D; i++) {
            aa[nl][j][i] = aa[nl-1][k][i-1] + b[nl-1][i] * c[nl-1][1];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.4

real_t s141(struct args_t * func_args)
{

//    nonlinear dependence testing
//    walk a row in a symmetric packed array
//    element a(i,j) for (int j>i) stored in location j*(j-1)/2+i

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int k;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_2D; i++) {
            k = (i+1) * ((i+1) - 1) / 2 + (i+1)-1;
            for (int j = i; j < LEN_2D; j++) {
                flat_2d_array[nl][k] += bb[nl-1][j][i];
                k += j+1;
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.5

void s151s(real_t a[LEN_1D], real_t b[LEN_1D],  int m)
{
    for (int i = 0; i < LEN_1D-1; i++) {
        a[nl][i] = a[nl-1][i + m] + b[nl-1][i];
    }
}

real_t s151(struct args_t * func_args)
{

//    interprocedural data flow analysis
//    passing parameter information into a subroutine

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        s151s(a, b,  1);
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.5

void s152s(real_t a[LEN_1D], real_t b[LEN_1D], real_t c[LEN_1D], int i)
{
    a[nl][i] += b[nl-1][i] * c[nl-1][i];
}

real_t s152(struct args_t * func_args)
{

//    interprocedural data flow analysis
//    collecting information from a subroutine

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            b[nl][i] = d[nl-1][i] * e[nl-1][i];
            s152s(a, b, c, i);
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.6

real_t s161(struct args_t * func_args)
{

//    control flow
//    tests for recognition of loop independent dependences
//    between statements in mutually exclusive regions.

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D-1; ++i) {
            if (b[nl-1][i] < (real_t)0.) {
                goto L20;
            }
            a[nl][i] = c[nl-1][i] + d[nl-1][i] * e[nl-1][i];
            goto L10;
L20:
            c[nl][i+1] = a[nl-1][i] + d[nl-1][i] * d[nl-1][i];
L10:
            ;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1161(struct args_t * func_args)
{

//    control flow
//    tests for recognition of loop independent dependences
//    between statements in mutually exclusive regions.

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D-1; ++i) {
            if (c[nl-1][i] < (real_t)0.) {
                goto L20;
            }
            a[nl][i] = c[nl-1][i] + d[nl-1][i] * e[nl-1][i];
            goto L10;
L20:
            b[nl][i] = a[nl-1][i] + d[nl-1][i] * d[nl-1][i];
L10:
            ;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.6

//int s162(int k)
real_t s162(struct args_t * func_args)
{
//    control flow
//    deriving assertions

    int k = *(int*)func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        if (k > 0) {
            for (int i = 0; i < LEN_1D-1; i++) {
                a[nl][i] = a[nl-1][i + k] + b[nl-1][i] * c[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.7

//int s171(int inc)
real_t s171(struct args_t * func_args)
{

//    symbolics
//    symbolic dependence tests

    int inc = *(int*)func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i * inc] += b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.7

//int s172( int n1, int n3)
real_t s172(struct args_t * func_args)
{
//    symbolics
//    vectorizable if n3 .ne. 0

    struct{int a;int b;} * x = func_args->arg_info;
    int n1 = x->a;
    int n3 = x->b;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = n1-1; i < LEN_1D; i += n3) {
            a[nl][i] += b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.7

real_t s173(struct args_t * func_args)
{
//    symbolics
//    expression in loop bounds and subscripts

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int k = LEN_1D/2;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D/2; i++) {
            a[nl][i+k] = a[nl-1][i] + b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.7

//int s174(int M)
real_t s174(struct args_t * func_args)
{

//    symbolics
//    loop with subscript that may seem ambiguous

    int M = *(int*)func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < M; i++) {
            a[nl][i+M] = a[nl-1][i] + b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.7

//int s175(int inc)
real_t s175(struct args_t * func_args)
{

//    symbolics
//    symbolic dependence tests

    int inc = *(int*)func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D-1; i += inc) {
            a[nl][i] = a[nl-1][i + inc] + b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %1.7

real_t s176(struct args_t * func_args)
{

//    symbolics
//    convolution

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int m = LEN_1D/2;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int j = 0; j < (LEN_1D/2); j++) {
            for (int i = 0; i < m; i++) {
                a[nl][i] += b[nl-1][i+m-j-1] * c[nl-1][j];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// **********************************************************
// *                                *
// *            VECTORIZATION                *
// *                                *
// **********************************************************

// %2.1

real_t s211(struct args_t * func_args)
{

//    statement reordering
//    statement reordering allows vectorization

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_1D-1; i++) {
            a[nl][i] = b[nl-1][i - 1] + c[nl-1][i] * d[nl-1][i];
            b[nl][i] = b[nl-1][i + 1] - e[nl-1][i] * d[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.1

real_t s212(struct args_t * func_args)
{

//    statement reordering
//    dependency needing temporary

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D-1; i++) {
            a[nl][i] *= c[nl-1][i];
            b[nl][i] += a[nl-1][i + 1] * d[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1213(struct args_t * func_args)
{

//    statement reordering
//    dependency needing temporary

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_1D-1; i++) {
            a[nl][i] = b[nl-1][i-1]+c[i];
            b[nl][i] = a[nl-1][i+1]*d[i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.2

real_t s221(struct args_t * func_args)
{

//    loop distribution
//    loop that is partially recursive

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_1D; i++) {
            a[nl][i] += c[nl-1][i] * d[nl-1][i];
            b[nl][i] = b[nl-1][i - 1] + a[nl-1][i] + d[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1221(struct args_t * func_args)
{

//    run-time symbolic resolution

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 4; i < LEN_1D; i++) {
            b[nl][i] = b[nl-1][i - 4] + a[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.2

real_t s222(struct args_t * func_args)
{

//    loop distribution
//    partial loop vectorizatio recurrence in middle

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_1D; i++) {
            a[nl][i] += b[nl-1][i] * c[nl-1][i];
            e[nl][i] = e[nl-1][i - 1] * e[nl-1][i - 1];
            a[nl][i] -= b[nl-1][i] * c[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.3

real_t s231(struct args_t * func_args)
{
//    loop interchange
//    loop with data dependency

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_2D; ++i) {
            for (int j = 1; j < LEN_2D; j++) {
                aa[nl][j][i] = aa[nl-1][j - 1][i] + bb[nl-1][j][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.3

real_t s232(struct args_t * func_args)
{

//    loop interchange
//    interchanging of triangular loops

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int j = 1; j < LEN_2D; j++) {
            for (int i = 1; i <= j; i++) {
                aa[nl][j][i] = aa[nl-1][j][i-1]*aa[j][i-1]+bb[j][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 1.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1232(struct args_t * func_args)
{

//    loop interchange
//    interchanging of triangular loops

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int j = 0; j < LEN_2D; j++) {
            for (int i = j; i < LEN_2D; i++) {
                aa[nl][i][j] = bb[nl-1][i][j] + cc[nl-1][i][j];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 1.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.3

real_t s233(struct args_t * func_args)
{

//    loop interchange
//    interchanging with one of two inner loops

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_2D; i++) {
            for (int j = 1; j < LEN_2D; j++) {
                aa[nl][j][i] = aa[nl-1][j-1][i] + cc[nl-1][j][i];
            }
            for (int j = 1; j < LEN_2D; j++) {
                bb[nl][j][i] = bb[nl-1][j][i-1] + cc[nl-1][j][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s2233(struct args_t * func_args)
{

//    loop interchange
//    interchanging with one of two inner loops

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_2D; i++) {
            for (int j = 1; j < LEN_2D; j++) {
                aa[nl][j][i] = aa[nl-1][j-1][i] + cc[nl-1][j][i];
            }
            for (int j = 1; j < LEN_2D; j++) {
                bb[nl][i][j] = bb[nl-1][i-1][j] + cc[nl-1][i][j];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.3
real_t s235(struct args_t * func_args)
{

//    loop interchanging
//    imperfectly nested loops

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_2D; i++) {
            a[nl][i] += b[nl-1][i] * c[nl-1][i];
            for (int j = 1; j < LEN_2D; j++) {
                aa[nl][j][i] = aa[nl-1][j-1][i] + bb[nl-1][j][i] * a[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.4

real_t s241(struct args_t * func_args)
{

//    node splitting
//    preloading necessary to allow vectorization

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D-1; i++) {
            a[nl][i] = b[nl-1][i] * c[nl-1][i  ] * d[nl-1][i];
            b[nl][i] = a[nl-1][i] * a[nl-1][i+1] * d[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.4

//int s242(real_t s1, real_t s2)
real_t s242(struct args_t * func_args)
{

//    node splitting

    struct{real_t a;real_t b;} * x = func_args->arg_info;
    real_t s1 = x->a;
    real_t s2 = x->b;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_1D; ++i) {
            a[nl][i] = a[nl-1][i - 1] + s1 + s2 + b[nl-1][i] + c[nl-1][i] + d[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.4

real_t s243(struct args_t * func_args)
{

//    node splitting
//    false dependence cycle breaking

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D-1; i++) {
            a[nl][i] = b[nl-1][i] + c[nl-1][i] * d[nl-1][i];
            b[nl][i] = a[nl-1][i] + d[nl-1][i] * e[nl-1][i];
            a[nl][i] = b[nl-1][i] + a[nl-1][i+1] * d[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.4

real_t s244(struct args_t * func_args)
{

//    node splitting
//    false dependence cycle breaking

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D-1; ++i) {
            a[nl][i] = b[nl-1][i] + c[nl-1][i] * d[nl-1][i];
            b[nl][i] = c[nl-1][i] + b[nl-1][i];
            a[nl][i+1] = b[nl-1][i] + a[nl-1][i+1] * d[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1244(struct args_t * func_args)
{

//    node splitting
//    cycle with ture and anti dependency

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D-1; i++) {
            a[nl][i] = b[nl-1][i] + c[nl-1][i] * c[nl-1][i] + b[nl-1][i]*b[i] + c[nl-1][i];
            d[nl][i] = a[nl-1][i] + a[nl-1][i+1];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s2244(struct args_t * func_args)
{

//    node splitting
//    cycle with ture and anti dependency

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D-1; i++) {
            a[nl][i+1] = b[nl-1][i] + e[nl-1][i];
            a[nl][i] = b[nl-1][i] + c[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.5

real_t s251(struct args_t * func_args)
{

//    scalar and array expansion
//    scalar expansion

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t s;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            s = b[nl-1][i] + c[nl-1][i] * d[nl-1][i];
            a[nl][i] = s * s;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1251(struct args_t * func_args)
{

//    scalar and array expansion
//    scalar expansion

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t s;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            s = b[nl-1][i]+c[i];
            b[nl][i] = a[nl-1][i]+d[i];
            a[nl][i] = s*e[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s2251(struct args_t * func_args)
{

//    scalar and array expansion
//    scalar expansion

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        real_t s = (real_t)0.0;
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = s*e[nl-1][i];
            s = b[nl-1][i]+c[i];
            b[nl][i] = a[nl-1][i]+d[i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s3251(struct args_t * func_args)
{

//    scalar and array expansion
//    scalar expansion

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D-1; i++){
            a[nl][i+1] = b[nl-1][i]+c[i];
            b[nl][i]   = c[nl-1][i]*e[i];
            d[nl][i]   = a[nl-1][i]*e[i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.5

real_t s252(struct args_t * func_args)
{

//    scalar and array expansion
//    loop with ambiguous scalar temporary

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t t, s;
    for (int nl = 1; nl < LEN_3D nl++) {
        t = (real_t) 0.;
        for (int i = 0; i < LEN_1D; i++) {
            s = b[nl-1][i] * c[nl-1][i];
            a[nl][i] = s + t;
            t = s;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.5

real_t s253(struct args_t * func_args)
{

//    scalar and array expansion
//    scalar expansio assigned under if

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t s;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (a[nl-1][i] > b[i]) {
                s = a[nl-1][i] - b[nl-1][i] * d[nl-1][i];
                c[nl][i] += s;
                a[nl][i] = s;
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.5

real_t s254(struct args_t * func_args)
{

//    scalar and array expansion
//    carry around variable

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t x;
    for (int nl = 1; nl < LEN_3D nl++) {
        x = b[nl-1][LEN_1D-1];
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = (b[nl-1][i] + x) * (real_t).5;
            x = b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.5

real_t s255(struct args_t * func_args)
{

//    scalar and array expansion
//    carry around variables, 2 levels

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t x, y;
    for (int nl = 1; nl < LEN_3D nl++) {
        x = b[nl-1][LEN_1D-1];
        y = b[nl-1][LEN_1D-2];
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = (b[nl-1][i] + x + y) * (real_t).333;
            y = x;
            x = b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.5

real_t s256(struct args_t * func_args)
{

//    scalar and array expansion
//    array expansion

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_2D; i++) {
            for (int j = 1; j < LEN_2D; j++) {
                a[nl][j] = (real_t)1.0 - a[nl-1][j - 1];
                aa[nl][j][i] = a[nl-1][j] + bb[nl-1][j][i]*d[j];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.5

real_t s257(struct args_t * func_args)
{

//    scalar and array expansion
//    array expansion

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_2D; i++) {
            for (int j = 0; j < LEN_2D; j++) {
                a[nl][i] = aa[nl-1][j][i] - a[nl-1][i-1];
                aa[nl][j][i] = a[nl-1][i] + bb[nl-1][j][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s258(struct args_t * func_args)
{

//    scalar and array expansion
//    wrap-around scalar under an if

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t s;
    for (int nl = 1; nl < LEN_3D nl++) {
        s = 0.;
        for (int i = 0; i < LEN_2D; ++i) {
            if (a[nl-1][i] > 0.) {
                s = d[nl-1][i] * d[nl-1][i];
            }
            b[nl][i] = s * c[nl-1][i] + d[nl-1][i];
            e[nl][i] = (s + (real_t)1.) * aa[nl-1][0][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.7

real_t s261(struct args_t * func_args)
{

//    scalar and array expansion
//    wrap-around scalar under an if

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t t;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_1D; ++i) {
            t = a[nl-1][i] + b[nl-1][i];
            a[nl][i] = t + c[nl-1][i-1];
            t = c[nl-1][i] * d[nl-1][i];
            c[nl][i] = t;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s271(struct args_t * func_args)
{

//    control flow
//    loop with singularity handling

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (b[nl-1][i] > (real_t)0.) {
                a[nl][i] += b[nl-1][i] * c[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.7

//int s272(real_t t)
real_t s272(struct args_t * func_args)
{

//    control flow
//    loop with independent conditional

    int t = *(int*)func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (e[nl][i] >= t) {
                a[nl][i] += c[nl-1][i] * d[nl-1][i];
                b[nl][i] += c[nl-1][i] * c[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.7

real_t s273(struct args_t * func_args)
{

//    control flow
//    simple loop with dependent conditional

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] += d[nl-1][i] * e[nl-1][i];
            if (a[nl][i] < (real_t)0.)
                b[nl][i] += d[nl-1][i] * e[nl-1][i];
            c[nl][i] += a[nl-1][i] * d[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.7

real_t s274(struct args_t * func_args)
{

//    control flow
//    complex loop with dependent conditional

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = c[nl-1][i] + e[nl-1][i] * d[nl-1][i];
            if (a[nl-1][i] > (real_t)0.) {
                b[nl][i] = a[nl-1][i] + b[nl-1][i];
            } else {
                a[nl][i] = d[nl-1][i] * e[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.7

real_t s275(struct args_t * func_args)
{

//    control flow
//    if around inner loop, interchanging needed

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_2D; i++) {
            if (aa[nl-1][0][i] > (real_t)0.) {
                for (int j = 1; j < LEN_2D; j++) {
                    aa[nl][j][i] = aa[nl-1][j-1][i] + bb[nl-1][j][i] * cc[nl-1][j][i];
                }
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s2275(struct args_t * func_args)
{

//    loop distribution is needed to be able to interchange

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_2D; i++) {
            for (int j = 0; j < LEN_2D; j++) {
                aa[nl][j][i] = aa[nl-1][j][i] + bb[nl-1][j][i] * cc[nl-1][j][i];
            }
            a[nl][i] = b[nl-1][i] + c[nl-1][i] * d[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.7

real_t s276(struct args_t * func_args)
{

//    control flow
//    if test using loop index

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int mid = (LEN_1D/2);
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (i+1 < mid) {
                a[nl][i] += b[nl-1][i] * c[nl-1][i];
            } else {
                a[nl][i] += b[nl-1][i] * d[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.7
real_t s277(struct args_t * func_args)
{

//    control flow
//    test for dependences arising from guard variable computation.

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D-1; i++) {
                if (a[nl-1][i] >= (real_t)0.) {
                    goto L20;
                }
                if (b[nl-1][i] >= (real_t)0.) {
                    goto L30;
                }
                a[nl][i] += c[nl-1][i] * d[nl-1][i];
L30:
                b[nl][i+1] = c[nl-1][i] + d[nl-1][i] * e[nl-1][i];
L20:
;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.7

real_t s278(struct args_t * func_args)
{

//    control flow
//    if/goto to block if-then-else

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (a[nl-1][i] > (real_t)0.) {
                goto L20;
            }
            b[nl][i] = -b[nl-1][i] + d[nl-1][i] * e[nl-1][i];
            goto L30;
L20:
            c[nl][i] = -c[nl-1][i] + d[nl-1][i] * e[nl-1][i];
L30:
            a[nl][i] = b[nl-1][i] + c[nl-1][i] * d[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.7

real_t s279(struct args_t * func_args)
{

//    control flow
//    vector if/gotos

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (a[nl-1][i] > (real_t)0.) {
                goto L20;
            }
            b[nl][i] = -b[nl-1][i] + d[nl-1][i] * d[nl-1][i];
            if (b[nl][i] <= a[i]) {
                goto L30;
            }
            c[nl][i] += d[nl-1][i] * e[nl-1][i];
            goto L30;
L20:
            c[nl][i] = -c[nl-1][i] + e[nl-1][i] * e[nl-1][i];
L30:
            a[nl][i] = b[nl-1][i] + c[nl-1][i] * d[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1279(struct args_t * func_args)
{

//    control flow
//    vector if/gotos

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (a[nl-1][i] < (real_t)0.) {
                if (b[nl-1][i] > a[i]) {
                    c[nl][i] += d[nl-1][i] * e[nl-1][i];
                }
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.7

//int s2710( real_t x)
real_t s2710(struct args_t * func_args)
{

//    control flow
//    scalar and vector ifs

    int x = *(int*)func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (a[nl][i] > b[i]) {
                a[nl][i] += b[nl-1][i] * d[nl-1][i];
                if (LEN_1D > 10) {
                    c[nl][i] += d[nl-1][i] * d[nl-1][i];
                } else {
                    c[nl][i] = d[nl-1][i] * e[nl-1][i] + (real_t)1.;
                }
            } else {
                b[nl][i] = a[nl-1][i] + e[nl-1][i] * e[nl-1][i];
                if (x > (real_t)0.) {
                    c[nl][i] = a[nl-1][i] + d[nl-1][i] * d[nl-1][i];
                } else {
                    c[nl][i] += e[nl-1][i] * e[nl-1][i];
                }
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.7

real_t s2711(struct args_t * func_args)
{

//    control flow
//    semantic if removal

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (b[nl][i] != (real_t)0.0) {
                a[nl][i] += b[nl-1][i] * c[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.7

real_t s2712(struct args_t * func_args)
{

//    control flow
//    if to elemental min

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (a[nl][i] > b[i]) {
                a[nl][i] += b[nl-1][i] * c[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.8

real_t s281(struct args_t * func_args)
{

//    crossing thresholds
//    index set splitting
//    reverse data access

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t x;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            x = a[nl-1][LEN_1D-i-1] + b[nl-1][i] * c[nl-1][i];
            a[nl][i] = x-(real_t)1.0;
            b[nl][i] = x;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1281(struct args_t * func_args)
{

//    crossing thresholds
//    index set splitting
//    reverse data access

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t x;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            x = b[nl-1][i]*c[i] + a[nl-1][i]*d[i] + e[nl-1][i];
            a[nl][i] = x-(real_t)1.0;
            b[nl][i] = x;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.9

real_t s291(struct args_t * func_args)
{

//    loop peeling
//    wrap around variable, 1 level

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int im1;
    for (int nl = 1; nl < LEN_3D nl++) {
        im1 = LEN_1D-1;
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = (b[nl-1][i] + b[im1]) * (real_t).5;
            im1 = i;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.9

real_t s292(struct args_t * func_args)
{

//    loop peeling
//    wrap around variable, 2 levels
//    similar to S291

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int im1, im2;
    for (int nl = 1; nl < LEN_3D nl++) {
        im1 = LEN_1D-1;
        im2 = LEN_1D-2;
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = (b[nl-1][i] + b[nl-1][im1] + b[im2]) * (real_t).333;
            im2 = im1;
            im1 = i;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.9

real_t s293(struct args_t * func_args)
{

//    loop peeling
//    a(i)=a(0) with actual dependence cycle, loop is vectorizable

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = a[nl-1][0];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.10

real_t s2101(struct args_t * func_args)
{

//    diagonals
//    main diagonal calculation
//    jump in data access

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_2D; i++) {
            aa[nl][i][i] += bb[nl-1][i][i] * cc[nl-1][i][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.12

real_t s2102(struct args_t * func_args)
{

//    diagonals
//    identity matrix, best results vectorize both inner and outer loops

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_2D; i++) {
            for (int j = 0; j < LEN_2D; j++) {
                aa[nl][j][i] = (real_t)0.;
            }
            aa[nl][i][i] = (real_t)1.;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %2.11

real_t s2111(struct args_t * func_args)
{

//    wavefronts, it will make jump in data access

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int j = 1; j < LEN_2D; j++) {
            for (int i = 1; i < LEN_2D; i++) {
                aa[nl][j][i] = (aa[nl-1][j][i-1] + aa[j-1][i])/1.9;
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// **********************************************************
//                                *
//            IDIOM RECOGNITION            *
//                                *
// **********************************************************

// %3.1

real_t s311(struct args_t * func_args)
{

//    reductions
//    sum reduction

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t sum;
    for (int nl = 1; nl < LEN_3D nl++) {
        sum = (real_t)0.;
        for (int i = 0; i < LEN_1D; i++) {
            sum += a[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, sum);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t test(real_t* A){
  real_t s = (real_t)0.0;
  for (int i = 0; i < 4; i++)
    s += A[nl-1][i];
  return s;
}

real_t s31111(struct args_t * func_args)
{

//    reductions
//    sum reduction

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t sum;
    for (int nl = 1; nl < LEN_3D nl++) {
        sum = (real_t)0.;
        sum += test(a);
        sum += test(&a[4]);
        sum += test(&a[8]);
        sum += test(&a[12]);
        sum += test(&a[16]);
        sum += test(&a[20]);
        sum += test(&a[24]);
        sum += test(&a[28]);
        dummy(a, b, c, d, e, aa, bb, cc, sum);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %3.1

real_t s312(struct args_t * func_args)
{

//    reductions
//    product reduction

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t prod;
    for (int nl = 1; nl < LEN_3D nl++) {
        prod = (real_t)1.;
        for (int i = 0; i < LEN_1D; i++) {
            prod *= a[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, prod);
    }

    gettimeofday(&func_args->t2, NULL);
    return prod;
}

// %3.1
real_t s313(struct args_t * func_args)
{

//    reductions
//    dot product

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t dot;
    for (int nl = 1; nl < LEN_3D nl++) {
        dot = (real_t)0.;
        for (int i = 0; i < LEN_1D; i++) {
            dot += a[nl-1][i] * b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, dot);
    }

    gettimeofday(&func_args->t2, NULL);
    return dot;
}

// %3.1

real_t s314(struct args_t * func_args)
{

//    reductions
//    if to max reduction

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t x;
    for (int nl = 1; nl < LEN_3D nl++) {
        x = a[nl-1][0];
        for (int i = 0; i < LEN_1D; i++) {
            if (a[nl-1][i] > x) {
                x = a[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, x);
    }

    gettimeofday(&func_args->t2, NULL);
    return x;
}

// %3.1

real_t s315(struct args_t * func_args)
{

//    reductions
//    if to max with index reductio 1 dimension

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int i = 0; i < LEN_1D; i++)
        a[nl][i] = (i * 7) % LEN_1D;

    real_t x, chksum;
    int index;
    for (int nl = 1; nl < LEN_3D nl++) {
        x = a[nl-1][0];
        index = 0;
        for (int i = 0; i < LEN_1D; ++i) {
            if (a[nl-1][i] > x) {
                x = a[nl-1][i];
                index = i;
            }
        }
        chksum = x + (real_t) index;
        dummy(a, b, c, d, e, aa, bb, cc, chksum);
    }

    gettimeofday(&func_args->t2, NULL);
    return index + x + 1;
}

// %3.1

real_t s316(struct args_t * func_args)
{

//    reductions
//    if to min reduction

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t x;
    for (int nl = 1; nl < LEN_3D nl++) {
        x = a[nl-1][0];
        for (int i = 1; i < LEN_1D; ++i) {
            if (a[nl-1][i] < x) {
                x = a[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, x);
    }

    gettimeofday(&func_args->t2, NULL);
    return x;
}
// %3.1

real_t s317(struct args_t * func_args)
{

//    reductions
//    product reductio vectorize with
//    1. scalar expansion of factor, and product reduction
//    2. closed form solution: q = factor**n

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t q;
    for (int nl = 1; nl < LEN_3D nl++) {
        q = (real_t)1.;
        for (int i = 0; i < LEN_1D/2; i++) {
            q *= (real_t).99;
        }
        dummy(a, b, c, d, e, aa, bb, cc, q);
    }

    gettimeofday(&func_args->t2, NULL);
    return q;
}

// %3.1

//int s318( int inc)
real_t s318(struct args_t * func_args)
{

//    reductions
//    isamax, max absolute value, increments not equal to 1

    int inc = *(int*)func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int k, index;
    real_t max, chksum;
    for (int nl = 1; nl < LEN_3D nl++) {
        k = 0;
        index = 0;
        max = ABS(a[0]);
        k += inc;
        for (int i = 1; i < LEN_1D; i++) {
            if (ABS(a[k]) <= max) {
                goto L5;
            }
            index = i;
            max = ABS(a[k]);
L5:
            k += inc;
        }
        chksum = max + (real_t) index;
        dummy(a, b, c, d, e, aa, bb, cc, chksum);
    }

    gettimeofday(&func_args->t2, NULL);
    return max + index + 1;
}

// %3.1

real_t s319(struct args_t * func_args)
{

//    reductions
//    coupled reductions

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t sum;
    for (int nl = 1; nl < LEN_3D nl++) {
        sum = 0.;
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = c[nl-1][i] + d[nl-1][i];
            sum += a[nl-1][i];
            b[nl][i] = c[nl-1][i] + e[nl-1][i];
            sum += b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, sum);
    }

    gettimeofday(&func_args->t2, NULL);
    return sum;
}

// %3.1

real_t s3110(struct args_t * func_args)
{

//    reductions
//    if to max with index reductio 2 dimensions
//    similar to S315

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int xindex, yindex;
    real_t max, chksum;
    for (int nl = 1; nl < LEN_3D nl++) {
        max = aa[nl-1][(0)][0];
        xindex = 0;
        yindex = 0;
        for (int i = 0; i < LEN_2D; i++) {
            for (int j = 0; j < LEN_2D; j++) {
                if (aa[nl-1][i][j] > max) {
                    max = aa[nl-1][i][j];
                    xindex = i;
                    yindex = j;
                }
            }
        }
        chksum = max + (real_t) xindex + (real_t) yindex;
        dummy(a, b, c, d, e, aa, bb, cc, chksum);
    }

    gettimeofday(&func_args->t2, NULL);
    return max + xindex+1 + yindex+1;
}

real_t s13110(struct args_t * func_args)
{

//    reductions
//    if to max with index reductio 2 dimensions

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int xindex, yindex;
    real_t max, chksum;
    for (int nl = 1; nl < LEN_3D nl++) {
        max = aa[nl-1][(0)][0];
        xindex = 0;
        yindex = 0;
        for (int i = 0; i < LEN_2D; i++) {
            for (int j = 0; j < LEN_2D; j++) {
                if (aa[nl-1][i][j] > max) {
                    max = aa[nl-1][i][j];
                    xindex = i;
                    yindex = j;
                }
            }
        }
        chksum = max + (real_t) xindex + (real_t) yindex;
        dummy(a, b, c, d, e, aa, bb, cc, chksum);
    }

    gettimeofday(&func_args->t2, NULL);
    return max + xindex+1 + yindex+1;
}

// %3.1

real_t s3111(struct args_t * func_args)
{

//    reductions
//    conditional sum reduction

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t sum;
    for (int nl = 1; nl < LEN_3D nl++) {
        sum = 0.;
        for (int i = 0; i < LEN_1D; i++) {
            if (a[nl-1][i] > (real_t)0.) {
                sum += a[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, sum);
    }

    gettimeofday(&func_args->t2, NULL);
    return sum;
}

// %3.1

real_t s3112(struct args_t * func_args)
{

//    reductions
//    sum reduction saving running sums

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t sum;
    for (int nl = 1; nl < LEN_3D nl++) {
        sum = (real_t)0.0;
        for (int i = 0; i < LEN_1D; i++) {
            sum += a[nl-1][i];
            b[nl][i] = sum;
        }
        dummy(a, b, c, d, e, aa, bb, cc, sum);
    }

    gettimeofday(&func_args->t2, NULL);
    return sum;
}

// %3.1

real_t s3113(struct args_t * func_args)
{

//    reductions
//    maximum of absolute value

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t max;
    for (int nl = 1; nl < LEN_3D nl++) {
        max = ABS(a[0]);
        for (int i = 0; i < LEN_1D; i++) {
            if ((ABS(a[i])) > max) {
                max = ABS(a[i]);
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, max);
    }

    gettimeofday(&func_args->t2, NULL);
    return max;
}

// %3.2

real_t s321(struct args_t * func_args)
{

//    recurrences
//    first order linear recurrence

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_1D; i++) {
            a[nl][i] += a[nl-1][i-1] * b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %3.2

real_t s322(struct args_t * func_args)
{

//    recurrences
//    second order linear recurrence

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 2; i < LEN_1D; i++) {
            a[nl][i] = a[nl-1][i] + a[nl-1][i - 1] * b[nl-1][i] + a[nl-1][i - 2] * c[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %3.2

real_t s323(struct args_t * func_args)
{

//    recurrences
//    coupled recurrence

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 1; i < LEN_1D; i++) {
            a[nl][i] = b[nl-1][i-1] + c[nl-1][i] * d[nl-1][i];
            b[nl][i] = a[nl-1][i] + c[nl-1][i] * e[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %3.3

real_t s331(struct args_t * func_args)
{

//    search loops
//    if to last-1

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int j;
    real_t chksum;
    for (int nl = 1; nl < LEN_3D nl++) {
        j = -1;
        for (int i = 0; i < LEN_1D; i++) {
            if (a[nl-1][i] < (real_t)0.) {
                j = i;
            }
        }
        chksum = (real_t) j;
        dummy(a, b, c, d, e, aa, bb, cc, chksum);
    }

    gettimeofday(&func_args->t2, NULL);
    return j+1;
}

// %3.3
//int s332( real_t t)
real_t s332(struct args_t * func_args)
{

//    search loops
//    first value greater than threshold

    int t = *(int*)func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int index;
    real_t value;
    real_t chksum;
    for (int nl = 1; nl < LEN_3D nl++) {
        index = -2;
        value = -1.;
        for (int i = 0; i < LEN_1D; i++) {
            if (a[nl-1][i] > t) {
                index = i;
                value = a[nl-1][i];
                goto L20;
            }
        }
L20:
        chksum = value + (real_t) index;
        dummy(a, b, c, d, e, aa, bb, cc, chksum);
    }

    gettimeofday(&func_args->t2, NULL);
    return value;
}

// %3.4

real_t s341(struct args_t * func_args)
{

//    packing
//    pack positive values
//    not vectorizable, value of j in unknown at each iteration

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int j;
    for (int nl = 1; nl < LEN_3D nl++) {
        j = -1;
        for (int i = 0; i < LEN_1D; i++) {
            if (b[nl-1][i] > (real_t)0.) {
                j++;
                a[nl][j] = b[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %3.4

real_t s342(struct args_t * func_args)
{

//    packing
//    unpacking
//    not vectorizable, value of j in unknown at each iteration

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int j = 0;
    for (int nl = 1; nl < LEN_3D nl++) {
        j = -1;
        for (int i = 0; i < LEN_1D; i++) {
            if (a[nl-1][i] > (real_t)0.) {
                j++;
                a[nl][i] = b[nl-1][j];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %3.4

real_t s343(struct args_t * func_args)
{

//    packing
//    pack 2-d array into one dimension
//    not vectorizable, value of k in unknown at each iteration

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int k;
    for (int nl = 1; nl < LEN_3D nl++) {
        k = -1;
        for (int i = 0; i < LEN_2D; i++) {
            for (int j = 0; j < LEN_2D; j++) {
                if (bb[nl-1][j][i] > (real_t)0.) {
                    k++;
                    flat_2d_array[nl][k] = aa[nl-1][j][i];
                }
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %3.5

real_t s351(struct args_t * func_args)
{

//    loop rerolling
//    unrolled saxpy

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t alpha = c[nl-1][0];
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i += 5) {
            a[nl][i] += alpha * b[nl-1][i];
            a[nl][i + 1] += alpha * b[nl-1][i + 1];
            a[nl][i + 2] += alpha * b[nl-1][i + 2];
            a[nl][i + 3] += alpha * b[nl-1][i + 3];
            a[nl][i + 4] += alpha * b[nl-1][i + 4];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1351(struct args_t * func_args)
{

//    induction pointer recognition

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        real_t* __restrict__ A = a;
        real_t* __restrict__ B = b;
        real_t* __restrict__ C = c;
        for (int i = 0; i < LEN_1D; i++) {
            *A = *B+*C;
            A++;
            B++;
            C++;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %3.5

real_t s352(struct args_t * func_args)
{

//    loop rerolling
//    unrolled dot product

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t dot;
    for (int nl = 1; nl < LEN_3D nl++) {
        dot = (real_t)0.;
        for (int i = 0; i < LEN_1D; i += 5) {
            dot = dot + a[nl-1][i] * b[nl-1][i] + a[nl-1][i + 1] * b[nl-1][i + 1] + a[i + 2]
                * b[nl-1][i + 2] + a[nl-1][i + 3] * b[nl-1][i + 3] + a[nl-1][i + 4] * b[nl-1][i + 4];
        }
        dummy(a, b, c, d, e, aa, bb, cc, dot);
    }

    gettimeofday(&func_args->t2, NULL);
    return dot;
}

// %3.5

//int s353(int* __restrict__ ip)
real_t s353(struct args_t * func_args)
{

//    loop rerolling
//    unrolled sparse saxpy
//    gather is required

    int * __restrict__ ip = func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t alpha = c[nl-1][0];
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i += 5) {
            a[nl][i] += alpha * b[nl-1][ip[i]];
            a[nl][i + 1] += alpha * b[nl-1][ip[i + 1]];
            a[nl][i + 2] += alpha * b[nl-1][ip[i + 2]];
            a[nl][i + 3] += alpha * b[nl-1][ip[i + 3]];
            a[nl][i + 4] += alpha * b[nl-1][ip[i + 4]];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// **********************************************************
//                                *
//             LANGUAGE COMPLETENESS            *
//                                *
// **********************************************************

// %4.1
// %4.2

real_t s421(struct args_t * func_args)
{

//    storage classes and equivalencing
//    equivalence- no overlap

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    xx = flat_2d_array;

    for (int nl = 1; nl < LEN_3D nl++) {
        yy = xx;
        for (int i = 0; i < LEN_1D - 1; i++) {
            xx[nl][i] = yy[nl-1][i+1] + a[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 1.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

real_t s1421(struct args_t * func_args)
{

//    storage classes and equivalencing
//    equivalence- no overlap

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    xx = &b[nl-1][LEN_1D/2];

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D/2; i++) {
            b[nl][i] = xx[nl-1][i] + a[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 1.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.2

real_t s422(struct args_t * func_args)
{

//    storage classes and equivalencing
//    common and equivalence statement
//    anti-dependence, threshold of 4

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    xx = flat_2d_array + 4;

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            xx[nl][i] = flat_2d_array[nl-1][i + 8] + a[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.2

real_t s423(struct args_t * func_args)
{

//    storage classes and equivalencing
//    common and equivalenced variables - with anti-dependence

    // do this again here
    int vl = 64;
    xx = flat_2d_array + vl;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D - 1; i++) {
            flat_2d_array[nl][i+1] = xx[nl-1][i] + a[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 1.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.2

real_t s424(struct args_t * func_args)
{

//    storage classes and equivalencing
//    common and equivalenced variables - overlap
//    vectorizeable in strips of 64 or less

    // do this again here
    int vl = 63;
    xx = flat_2d_array + vl;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D - 1; i++) {
            xx[nl][i+1] = flat_2d_array[nl-1][i] + a[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 1.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.3

real_t s431(struct args_t * func_args)
{

//    parameters
//    parameter statement

    int k1=1;
    int k2=2;
    int k=2*k1-k2;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = a[nl-1][i+k] + b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.4

real_t s441(struct args_t * func_args)
{

//    non-logical if's
//    arithmetic if

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (d[nl][i] < (real_t)0.) {
                a[nl][i] += b[nl-1][i] * c[nl-1][i];
            } else if (d[nl][i] == (real_t)0.) {
                a[nl][i] += b[nl-1][i] * b[nl-1][i];
            } else {
                a[nl][i] += c[nl-1][i] * c[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.4

real_t s442(struct args_t * func_args)
{

//    non-logical if's
//    computed goto

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            switch (indx[i]) {
                case 1:  goto L15;
                case 2:  goto L20;
                case 3:  goto L30;
                case 4:  goto L40;
            }
L15:
            a[nl][i] += b[nl-1][i] * b[nl-1][i];
            goto L50;
L20:
            a[nl][i] += c[nl-1][i] * c[nl-1][i];
            goto L50;
L30:
            a[nl][i] += d[nl-1][i] * d[nl-1][i];
            goto L50;
L40:
            a[nl][i] += e[nl-1][i] * e[nl-1][i];
L50:
            ;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.4

real_t s443(struct args_t * func_args)
{

//    non-logical if's
//    arithmetic if

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (d[nl][i] <= (real_t)0.) {
                goto L20;
            } else {
                goto L30;
            }
L20:
            a[nl][i] += b[nl-1][i] * c[nl-1][i];
            goto L50;
L30:
            a[nl][i] += b[nl-1][i] * b[nl-1][i];
L50:
            ;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.5

real_t s451(struct args_t * func_args)
{

//    intrinsic functions
//    intrinsics

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = sinf(b[i]) + cosf(c[i]);
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.5

real_t s452(struct args_t * func_args)
{

//    intrinsic functions
//    seq function

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = b[nl-1][i] + c[nl-1][i] * (real_t) (i+1);
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.5

real_t s453(struct args_t * func_args)
{

//    induction varibale recognition

    real_t s;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        s = 0.;
        for (int i = 0; i < LEN_1D; i++) {
            s += (real_t)2.;
            a[nl][i] = s * b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.7

int s471s(void)
{
// --  dummy subroutine call made in s471
    return 0;
}

real_t s471(struct args_t * func_args){

//    call statements

    int m = LEN_1D;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < m; i++) {
            x[nl][i] = b[nl-1][i] + d[nl-1][i] * d[nl-1][i];
            s471s();
            b[nl][i] = c[nl-1][i] + d[nl-1][i] * e[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.8

real_t s481(struct args_t * func_args)
{

//    non-local goto's
//    stop statement

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (d[nl-1][i] < (real_t)0.) {
                exit (0);
            }
            a[nl][i] += b[nl-1][i] * c[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.8

// %4.8
real_t s482(struct args_t * func_args)
{

//    non-local goto's
//    other loop exit with code before exit

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] += b[nl-1][i] * c[nl-1][i];
            if (c[nl][i] > b[i]) break;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.9

//int s491(int* __restrict__ ip)
real_t s491(struct args_t * func_args)
{

//    vector semantics
//    indirect addressing on lhs, store in sequence
//    scatter is required

    int * __restrict__ ip = func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][ip[i]] = b[nl-1][i] + c[nl-1][i] * d[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.11

//int s4112(int* __restrict__ ip, real_t s)
real_t s4112(struct args_t * func_args)
{

//    indirect addressing
//    sparse saxpy
//    gather is required

    struct{int * __restrict__ a;real_t b;} * x = func_args->arg_info;
    int * __restrict__ ip = x->a;
    real_t s = x->b;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] += b[nl-1][ip[i]] * s;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.11

//int s4113(int* __restrict__ ip)
real_t s4113(struct args_t * func_args)
{

//    indirect addressing
//    indirect addressing on rhs and lhs
//    gather and scatter is required

    int * __restrict__ ip = func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][ip[i]] = b[nl-1][ip[i]] + c[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.11

//int s4114(int* ip, int n1)
real_t s4114(struct args_t * func_args)
{

//    indirect addressing
//    mix indirect addressing with variable lower and upper bounds
//    gather is required

    struct{int * __restrict__ a;int b;} * x = func_args->arg_info;
    int * __restrict__ ip = x->a;
    int n1 = x->b;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    int k;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = n1-1; i < LEN_1D; i++) {
            k = ip[nl-1][i];
            a[nl][i] = b[nl-1][i] + c[nl-1][LEN_1D-k+1-2] * d[nl-1][i];
            k += 5;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.11

//int s4115(int* __restrict__ ip)
real_t s4115(struct args_t * func_args)
{

//    indirect addressing
//    sparse dot product
//    gather is required

    int * __restrict__ ip = func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t sum;
    for (int nl = 1; nl < LEN_3D nl++) {
        sum = 0.;
        for (int i = 0; i < LEN_1D; i++) {
            sum += a[nl-1][i] * b[nl-1][ip[i]];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return sum;
}

// %4.11

//int s4116(int* __restrict__ ip, int j, int inc)
real_t s4116(struct args_t * func_args)
{

//    indirect addressing
//    more complicated sparse sdot
//    gather is required

    struct{int * __restrict__ a;int b;int c;} * x = func_args->arg_info;
    int * __restrict__ ip = x->a;
    int j = x->b;
    int inc = x->c;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t sum;
    int off;
    for (int nl = 1; nl < LEN_3D nl++) {
        sum = 0.;
        for (int i = 0; i < LEN_2D-1; i++) {
            off = inc + i;
            sum += a[nl-1][off] * aa[nl-1][j-1][ip[i]];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return sum;
}

// %4.11

real_t s4117(struct args_t * func_args)
{

//    indirect addressing
//    seq function

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = b[nl-1][i] + c[nl-1][i/2] * d[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %4.12

real_t f(real_t a, real_t b){
    return a*b;
}

real_t s4121(struct args_t * func_args)
{

//    statement functions
//    elementwise multiplication

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] += f(b[i],c[i]);
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %5.1

real_t va(struct args_t * func_args)
{

//    control loops
//    vector assignment

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %5.1

//int vag( int* __restrict__ ip)
real_t vag(struct args_t * func_args)
{

//    control loops
//    vector assignment, gather
//    gather is required

    int * __restrict__ ip = func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = b[nl-1][ip[i]];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %5.1

//int vas( int* __restrict__ ip)
real_t vas(struct args_t * func_args)
{

//    control loops
//    vector assignment, scatter
//    scatter is required

    int * __restrict__ ip = func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][ip[i]] = b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %5.1

real_t vif(struct args_t * func_args)
{

//    control loops
//    vector if

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            if (b[nl-1][i] > (real_t)0.) {
                a[nl][i] = b[nl-1][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %5.1

real_t vpv(struct args_t * func_args)
{

//    control loops
//    vector plus vector

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] += b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %5.1

real_t vtv(struct args_t * func_args)
{

//    control loops
//    vector times vector

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] *= b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %5.1

real_t vpvtv(struct args_t * func_args)
{

//    control loops
//    vector plus vector times vector

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] += b[nl-1][i] * c[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %5.1

//real_t vpvts( real_t s)
real_t vpvts(struct args_t * func_args)
{

//    control loops
//    vector plus vector times scalar

    real_t s = *(int*)func_args->arg_info;

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] += b[nl-1][i] * s;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %5.1

real_t vpvpv(struct args_t * func_args)
{

//    control loops
//    vector plus vector plus vector

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] += b[nl-1][i] + c[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %5.1

real_t vtvtv(struct args_t * func_args)
{

//    control loops
//    vector times vector times vector

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[nl][i] = a[nl-1][i] * b[nl-1][i] * c[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

// %5.1

real_t vsumr(struct args_t * func_args)
{

//    control loops
//    vector sum reduction

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t sum;
    for (int nl = 1; nl < LEN_3D nl++) {
        sum = 0.;
        for (int i = 0; i < LEN_1D; i++) {
            sum += a[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, sum);
    }

    gettimeofday(&func_args->t2, NULL);
    return sum;
}

// %5.1

real_t vdotr(struct args_t * func_args)
{

//    control loops
//    vector dot product reduction

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t dot;
    for (int nl = 1; nl < LEN_3D nl++) {
        dot = 0.;
        for (int i = 0; i < LEN_1D; i++) {
            dot += a[nl-1][i] * b[nl-1][i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, dot);
    }

    gettimeofday(&func_args->t2, NULL);
    return dot;
}

// %5.1

real_t vbor(struct args_t * func_args)
{

//    control loops
//    basic operations rates, isolate arithmetic from memory traffic
//    all combinations of three, 59 flops for 6 loads and 1 store.

    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    real_t a1, b1, c1, d1, e1, f1;
    for (int nl = 1; nl < LEN_3D nl++) {
        for (int i = 0; i < LEN_2D; i++) {
            a1 = a[nl-1][i];
            b1 = b[nl-1][i];
            c1 = c[nl-1][i];
            d1 = d[nl-1][i];
            e1 = e[nl-1][i];
            f1 = aa[nl-1][0][i];
            a1 = a1 * b1 * c1 + a1 * b1 * d1 + a1 * b1 * e1 + a1 * b1 * f1 +
                a1 * c1 * d1 + a1 * c1 * e1 + a1 * c1 * f1 + a1 * d1 * e1
                + a1 * d1 * f1 + a1 * e1 * f1;
            b1 = b1 * c1 * d1 + b1 * c1 * e1 + b1 * c1 * f1 + b1 * d1 * e1 +
                b1 * d1 * f1 + b1 * e1 * f1;
            c1 = c1 * d1 * e1 + c1 * d1 * f1 + c1 * e1 * f1;
            d1 = d1 * e1 * f1;
            x[nl][i] = a1 * b1 * c1 * d1;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

typedef real_t(*test_function_t)(struct args_t *);

void time_function(test_function_t vector_func, void * arg_info)
{
    struct args_t func_args = {.arg_info=arg_info};

    double result = vector_func(&func_args);

    double tic=func_args.t1.tv_sec+(func_args.t1.tv_usec/1000000.0);
    double toc=func_args.t2.tv_sec+(func_args.t2.tv_usec/1000000.0);

    double taken = toc-tic;

    printf("%10.3f\t%f\n", taken, result);
}

int main(int argc, char ** argv){
    int n1 = 1;
    int n3 = 1;
    int* ip;
    real_t s1,s2;
    init(&ip, &s1, &s2);
    printf("Loop \tTime(sec) \tChecksum\n");

    time_function(&s000, NULL);
    time_function(&s111, NULL);
    time_function(&s1111, NULL);
    time_function(&s112, NULL);
    time_function(&s1112, NULL);
    time_function(&s113, NULL);
    time_function(&s1113, NULL);
    time_function(&s114, NULL);
    time_function(&s115, NULL);
    time_function(&s1115, NULL);
    time_function(&s116, NULL);
    time_function(&s118, NULL);
    time_function(&s119, NULL);
    time_function(&s1119, NULL);
    time_function(&s121, NULL);
    time_function(&s122, &(struct{int a;int b;}){n1, n3});
    time_function(&s123, NULL);
    time_function(&s124, NULL);
    time_function(&s125, NULL);
    time_function(&s126, NULL);
    time_function(&s127, NULL);
    time_function(&s128, NULL);
    time_function(&s131, NULL);
    time_function(&s132, NULL);
    time_function(&s141, NULL);
    time_function(&s151, NULL);
    time_function(&s152, NULL);
    time_function(&s161, NULL);
    time_function(&s1161, NULL);
    time_function(&s162, &n1);
    time_function(&s171, &n1);
    time_function(&s172, &(struct{int a;int b;}){n1, n3});
    time_function(&s173, NULL);
    time_function(&s174, &(struct{int a;}){LEN_1D/2});
    time_function(&s175, &n1);
    time_function(&s176, NULL);
    time_function(&s211, NULL);
    time_function(&s212, NULL);
    time_function(&s1213, NULL);
    time_function(&s221, NULL);
    time_function(&s1221, NULL);
    time_function(&s222, NULL);
    time_function(&s231, NULL);
    time_function(&s232, NULL);
    time_function(&s1232, NULL);
    time_function(&s233, NULL);
    time_function(&s2233, NULL);
    time_function(&s235, NULL);
    time_function(&s241, NULL);
    time_function(&s242, &(struct{real_t a;real_t b;}){s1, s2});
    time_function(&s243, NULL);
    time_function(&s244, NULL);
    time_function(&s1244, NULL);
    time_function(&s2244, NULL);
    time_function(&s251, NULL);
    time_function(&s1251, NULL);
    time_function(&s2251, NULL);
    time_function(&s3251, NULL);
    time_function(&s252, NULL);
    time_function(&s253, NULL);
    time_function(&s254, NULL);
    time_function(&s255, NULL);
    time_function(&s256, NULL);
    time_function(&s257, NULL);
    time_function(&s258, NULL);
    time_function(&s261, NULL);
    time_function(&s271, NULL);
    time_function(&s272, &s1);
    time_function(&s273, NULL);
    time_function(&s274, NULL);
    time_function(&s275, NULL);
    time_function(&s2275, NULL);
    time_function(&s276, NULL);
    time_function(&s277, NULL);
    time_function(&s278, NULL);
    time_function(&s279, NULL);
    time_function(&s1279, NULL);
    time_function(&s2710, &s1);
    time_function(&s2711, NULL);
    time_function(&s2712, NULL);
    time_function(&s281, NULL);
    time_function(&s1281, NULL);
    time_function(&s291, NULL);
    time_function(&s292, NULL);
    time_function(&s293, NULL);
    time_function(&s2101, NULL);
    time_function(&s2102, NULL);
    time_function(&s2111, NULL);
    time_function(&s311, NULL);
    time_function(&s31111, NULL);
    time_function(&s312, NULL);
    time_function(&s313, NULL);
    time_function(&s314, NULL);
    time_function(&s315, NULL);
    time_function(&s316, NULL);
    time_function(&s317, NULL);
    time_function(&s318, &n1);
    time_function(&s319, NULL);
    time_function(&s3110, NULL);
    time_function(&s13110, NULL);
    time_function(&s3111, NULL);
    time_function(&s3112, NULL);
    time_function(&s3113, NULL);
    time_function(&s321, NULL);
    time_function(&s322, NULL);
    time_function(&s323, NULL);
    time_function(&s331, NULL);
    time_function(&s332, &s1);
    time_function(&s341, NULL);
    time_function(&s342, NULL);
    time_function(&s343, NULL);
    time_function(&s351, NULL);
    time_function(&s1351, NULL);
    time_function(&s352, NULL);
    time_function(&s353, ip);
    time_function(&s421, NULL);
    time_function(&s1421, NULL);
    time_function(&s422, NULL);
    time_function(&s423, NULL);
    time_function(&s424, NULL);
    time_function(&s431, NULL);
    time_function(&s441, NULL);
    time_function(&s442, NULL);
    time_function(&s443, NULL);
    time_function(&s451, NULL);
    time_function(&s452, NULL);
    time_function(&s453, NULL);
    time_function(&s471, NULL);
    time_function(&s481, NULL);
    time_function(&s482, NULL);
    time_function(&s491, ip);
    time_function(&s4112, &(struct{int*a;real_t b;}){ip, s1});
    time_function(&s4113, ip);
    time_function(&s4114, &(struct{int*a;int b;}){ip, n1});
    time_function(&s4115, ip);
    time_function(&s4116, &(struct{int * a; int b; int c;}){ip, LEN_2D/2, n1});
    time_function(&s4117, NULL);
    time_function(&s4121, NULL);
    time_function(&va, NULL);
    time_function(&vag, ip);
    time_function(&vas, ip);
    time_function(&vif, NULL);
    time_function(&vpv, NULL);
    time_function(&vtv, NULL);
    time_function(&vpvtv, NULL);
    time_function(&vpvts, &s1);
    time_function(&vpvpv, NULL);
    time_function(&vtvtv, NULL);
    time_function(&vsumr, NULL);
    time_function(&vdotr, NULL);
    time_function(&vbor, NULL);

    return EXIT_SUCCESS;
}
