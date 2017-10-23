/* crzt02.f -- translated by f2c (version 20061008).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"
#include "blaswrap.h"

/* Table of constant values */

static integer c__7 = 7;
static complex c_b5 = {0.f,0.f};
static complex c_b6 = {1.f,0.f};

doublereal crzt02_(integer *m, integer *n, complex *af, integer *lda, complex 
	*tau, complex *work, integer *lwork)
{
    /* System generated locals */
    integer af_dim1, af_offset, i__1, i__2, i__3;
    real ret_val;
    complex q__1;

    /* Local variables */
    integer i__, info;
    real rwork[1];
    extern doublereal clange_(char *, integer *, integer *, complex *, 
	    integer *, real *), slamch_(char *);
    extern /* Subroutine */ int claset_(char *, integer *, integer *, complex 
	    *, complex *, complex *, integer *), xerbla_(char *, 
	    integer *), cunmrz_(char *, char *, integer *, integer *, 
	    integer *, integer *, complex *, integer *, complex *, complex *, 
	    integer *, complex *, integer *, integer *);


/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  CRZT02 returns */
/*       || I - Q'*Q || / ( M * eps) */
/*  where the matrix Q is defined by the Householder transformations */
/*  generated by CTZRZF. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix AF. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix AF. */

/*  AF      (input) COMPLEX array, dimension (LDA,N) */
/*          The output of CTZRZF. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array AF. */

/*  TAU     (input) COMPLEX array, dimension (M) */
/*          Details of the Householder transformations as returned by */
/*          CTZRZF. */

/*  WORK    (workspace) COMPLEX array, dimension (LWORK) */

/*  LWORK   (input) INTEGER */
/*          Length of WORK array. LWORK >= N*N+N. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    af_dim1 = *lda;
    af_offset = 1 + af_dim1;
    af -= af_offset;
    --tau;
    --work;

    /* Function Body */
    ret_val = 0.f;

    if (*lwork < *n * *n + *n) {
	xerbla_("CRZT02", &c__7);
	return ret_val;
    }

/*     Quick return if possible */

    if (*m <= 0 || *n <= 0) {
	return ret_val;
    }

/*     Q := I */

    claset_("Full", n, n, &c_b5, &c_b6, &work[1], n);

/*     Q := P(1) * ... * P(m) * Q */

    i__1 = *n - *m;
    i__2 = *lwork - *n * *n;
    cunmrz_("Left", "No transpose", n, n, m, &i__1, &af[af_offset], lda, &tau[
	    1], &work[1], n, &work[*n * *n + 1], &i__2, &info);

/*     Q := P(m)' * ... * P(1)' * Q */

    i__1 = *n - *m;
    i__2 = *lwork - *n * *n;
    cunmrz_("Left", "Conjugate transpose", n, n, m, &i__1, &af[af_offset], 
	    lda, &tau[1], &work[1], n, &work[*n * *n + 1], &i__2, &info);

/*     Q := Q - I */

    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = (i__ - 1) * *n + i__;
	i__3 = (i__ - 1) * *n + i__;
	q__1.r = work[i__3].r - 1.f, q__1.i = work[i__3].i;
	work[i__2].r = q__1.r, work[i__2].i = q__1.i;
/* L10: */
    }

    ret_val = clange_("One-norm", n, n, &work[1], n, rwork) / (
	    slamch_("Epsilon") * (real) max(*m,*n));
    return ret_val;

/*     End of CRZT02 */

} /* crzt02_ */
