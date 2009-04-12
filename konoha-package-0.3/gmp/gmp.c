#include <gmp.h>
#include <konoha.h>

#ifndef KNH_GMP_
#define KNH_GMP_
mpz_t knh_mp;
#endif

static void knh_gmp_gfree(Ctx *ctx,knh_Glue_t *g){
    mpz_clear(knh_mp);
}

/* Gmp!   Gmp.init() */
METHOD Gmp_new(Ctx *ctx,knh_sfp_t *sfp){
    mpz_init(knh_mp);
    knh_Glue_init(ctx,sfp[0].glue,NULL,knh_gmp_gfree);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}


/* void   Gmp.init() */

METHOD Gmp_init(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_init(knh_mp);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.init2 (int n) */

METHOD Gmp_init2(Ctx *ctx, knh_sfp_t* sfp)
{
    int n = p_int(sfp[1]);
    mpz_init2(knh_mp,n);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.clear (Gmp integer) */

METHOD Gmp_clear(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_clear(knh_mp);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.set (Gmp rop, Gmp op) */

METHOD Gmp_set(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *mp = (mpz_t*) p_cptr(sfp[1]);
    mpz_set(knh_mp,*mp);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.setInt (Gmp rop, int op) */

METHOD Gmp_setInt(Ctx *ctx, knh_sfp_t* sfp)
{
    int op = p_int(sfp[1]);
    mpz_set_ui(knh_mp,op);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.setFloat (Gmp rop, float op) */

METHOD Gmp_setFloat(Ctx *ctx, knh_sfp_t* sfp)
{
    double op = (double) p_float(sfp[1]);
    mpz_set_d(knh_mp,op);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.set_q (Gmp rop, mpq_t op) */
/*
METHOD Gmp_set_q(Ctx *ctx, knh_sfp_t* sfp)
{

    KNH_RETURN_void(ctx, sfp);
}
*/

/* void   Gmp.set_f (Gmp rop, mpf_t op) */
/*
METHOD Gmp_set_f(Ctx *ctx, knh_sfp_t* sfp)
{

    KNH_RETURN_void(ctx, sfp);
}
*/

/* int    Gmp.setStr (String str, int base) */

METHOD Gmp_setStr(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *mp = (mpz_t*) p_cptr(sfp[0]);
    char* str = p_char(sfp[1]);
    int base  = p_int (sfp[2]);
    int ret = mpz_init_set_str(*mp ,str ,base );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void   Gmp.swap (Gmp rop1, Gmp rop2) */

METHOD Gmp_swap(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *mp1 = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *mp2 = (mpz_t*) p_cptr(sfp[2]);

    mpz_swap(*mp1,*mp2);
    KNH_RETURN_void(ctx, sfp);
}

/* void   Gmp.initSet (Gmp op) */

METHOD Gmp_initSet(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *mp = (mpz_t*) p_cptr(sfp[1]);
    mpz_init_set(knh_mp,*mp);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.initSetInt (Gmp rop, int op) */

METHOD Gmp_initSetInt(Ctx *ctx, knh_sfp_t* sfp)
{
    int op = p_int(sfp[1]);
    mpz_init_set_ui(knh_mp,op);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.init_set_d (Gmp rop, float op) */

METHOD Gmp_initSetDouble(Ctx *ctx, knh_sfp_t* sfp)
{
    double op = (double) p_float(sfp[1]);
    mpz_init_set_d(knh_mp,op);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int    Gmp.init_set_str (Gmp rop, Stringstr, int base) */

METHOD Gmp_initSetStr(Ctx *ctx, knh_sfp_t* sfp)
{
    char* str = p_char(sfp[1]);
    int   base= p_int (sfp[2]);
    int ret = mpz_init_set_str(knh_mp ,str,base );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.get_ui () */

METHOD Gmp_getInt(Ctx *ctx, knh_sfp_t* sfp)
{
    knh_int_t ret = mpz_get_ui(knh_mp);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* float Gmp.getFloat () */
METHOD Gmp_getFloat(Ctx *ctx, knh_sfp_t* sfp)
{
    double ret = mpz_get_d(knh_mp);
    KNH_RETURN_Float(ctx, sfp, ret);
}

/* float Gmp.getFloat2exp (int *exp) */
METHOD Gmp_getFloat2exp(Ctx *ctx, knh_sfp_t* sfp)
{
    signed long int exp = (signed long int)p_int(sfp[1]);
    double ret = mpz_get_d_2exp(&exp ,knh_mp);
    KNH_RETURN_Float(ctx, sfp, ret);
}

/* String Gmp.getString (int base) */
METHOD Gmp_getString(Ctx *ctx, knh_sfp_t* sfp)
{
    int base = p_int (sfp[1]);
    char ret[20];// = NULL;
    mpz_get_str(ret, base, knh_mp);

    KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* Gmp!   Gmp.add (Gmp op) */

METHOD Gmp_add(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op = (mpz_t*) p_cptr(sfp[1]);
    mpz_add(knh_mp,knh_mp,*op);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* Gmp!   Gmp.addInt (int op) */

METHOD Gmp_addInt(Ctx *ctx, knh_sfp_t* sfp)
{
    int op = p_int(sfp[1]);
    mpz_add_ui(knh_mp,knh_mp,op);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.sub (Gmp op) */
METHOD Gmp_sub(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op = (mpz_t*) p_cptr(sfp[1]);
    mpz_sub(knh_mp,knh_mp,*op);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.subInt ( int op) */
METHOD Gmp_subInt(Ctx *ctx, knh_sfp_t* sfp)
{
    int op = p_int(sfp[1]);
    mpz_sub_ui(knh_mp,knh_mp,op);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.iSub (int op) */
METHOD Gmp_iSub(Ctx *ctx, knh_sfp_t* sfp)
{
    int op = p_int(sfp[1]);
    mpz_ui_sub(knh_mp,op,knh_mp);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.mul (Gmp op) */
METHOD Gmp_mul(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op = (mpz_t*) p_cptr(sfp[1]);
    mpz_mul(knh_mp,knh_mp,*op);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.mulInt (int op) */

METHOD Gmp_mulInt(Ctx *ctx, knh_sfp_t* sfp)
{
    int op = p_int(sfp[1]);
    mpz_mul_ui(knh_mp,knh_mp,op);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.addmul (Gmp op1, Gmp op2) */

METHOD Gmp_addmul(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *op2 = (mpz_t*) p_cptr(sfp[2]);
    mpz_addmul(knh_mp,*op1,*op2);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.addmul_ui (Gmp op1, int op2) */

METHOD Gmp_addmulInt(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    int    op2 = p_int(sfp[2]);
    mpz_addmul_ui(knh_mp,*op1,op2);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.submul ( Gmp op1, Gmp op2) */
METHOD Gmp_submul(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *op2 = (mpz_t*) p_cptr(sfp[2]);
    mpz_submul(knh_mp,*op1,*op2);
    KNH_RETURN(ctx,sfp,sfp[0].o);

}

/* void   Gmp.submul_ui (Gmp op1, int op2) */
METHOD Gmp_submulInt(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    int    op2 = p_int(sfp[2]);
    mpz_submul_ui(knh_mp,*op1,op2);
    KNH_RETURN(ctx,sfp,sfp[0].o);


}

/* void   Gmp.mul_2exp (Gmp op1, int op2) */
METHOD Gmp_mul2exp(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    int op2 = p_int(sfp[2]);
    mpz_mul_2exp(knh_mp,*op1,op2);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.neg (Gmp rop, Gmp op) */

METHOD Gmp_neg(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_neg(knh_mp,knh_mp);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.abs (Gmp rop, Gmp op) */

METHOD Gmp_abs(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_abs(knh_mp,knh_mp);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.cdiv_q (Gmp q, Gmp n, Gmp d) */

METHOD Gmp_cdivQ(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *d = (mpz_t*) p_cptr(sfp[2]);
    mpz_cdiv_q(knh_mp,*n,*d);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.cdiv_r (Gmp r, Gmp n, Gmp d) */

METHOD Gmp_cdivR(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *d = (mpz_t*) p_cptr(sfp[2]);
    mpz_cdiv_r(knh_mp,*n,*d);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.cdiv_qr (Gmp r, Gmp n, Gmp d) */

METHOD Gmp_cdivQR(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *r = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *n = (mpz_t*) p_cptr(sfp[2]);
    mpz_t *d = (mpz_t*) p_cptr(sfp[3]);
    mpz_cdiv_qr(knh_mp,*r,*n,*d);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int    Gmp.cdiv_q_ui ( Gmp n, int d) */

METHOD Gmp_cdivQ2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    int d = p_int(sfp[2]);
    int ret = mpz_cdiv_q_ui(knh_mp,*n,d);
    KNH_RETURN_Int(ctx,sfp,ret);
}

/* int    Gmp.mp.cdiv_r_ui (Gmp n, int d) */

METHOD Gmp_cdivR2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    int d = p_int(sfp[2]);
    int ret = mpz_cdiv_r_ui(knh_mp,*n,d);
    KNH_RETURN_Int(ctx,sfp,ret);
}

/* int    Gmp.mp.cdiv_qr_ui (Gmp r, Gmp n, int d) */

METHOD Gmp_cdivQR2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *r = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *n = (mpz_t*) p_cptr(sfp[2]);
    int d = p_int(sfp[3]);
    int ret = mpz_cdiv_qr_ui(knh_mp,*r,*n,d);

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.cdiv_ui ( int d) */

METHOD Gmp_cdivInt(Ctx *ctx, knh_sfp_t* sfp)
{
    int d = p_int(sfp[1]);
    int ret = mpz_cdiv_ui(knh_mp,d);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void   Gmp.cdiv_q_2exp ( Gmp n, int b) */
METHOD Gmp_cdivQ2exp(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    int b = p_int(sfp[2]);
    mpz_cdiv_q_2exp(knh_mp,*n,b);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.cdiv_r_2exp ( Gmp n, int b) */
METHOD Gmp_cdivR2exp(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    int b = p_int(sfp[2]);
    mpz_cdiv_r_2exp(knh_mp,*n,b);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.fdiv_q ( Gmp n, Gmp d) */
METHOD Gmp_fdivQ(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *d = (mpz_t*) p_cptr(sfp[2]);
    mpz_fdiv_q(knh_mp,*n,*d);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.fdiv_r ( Gmp n, Gmp d) */

METHOD Gmp_fdivR(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *d = (mpz_t*) p_cptr(sfp[2]);
    mpz_fdiv_q(knh_mp,*n,*d);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.fdiv_qr (Gmp q, Gmp r, Gmp n, Gmp d) */

METHOD Gmp_fdivQR(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *r = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *n = (mpz_t*) p_cptr(sfp[2]);
    mpz_t *d = (mpz_t*) p_cptr(sfp[3]);
    mpz_fdiv_qr(knh_mp,*r,*n,*d);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}


/* int    Gmp_fdiv_q_ui (Gmp q, Gmp n, int d) */

METHOD Gmp_fdivQ2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    int d = p_int(sfp[2]);
    int ret = mpz_fdiv_q_ui(knh_mp,*n,d);

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.mp.fdiv_r_ui (Gmp r, Gmp n, int d) */

METHOD Gmp_fdivR2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    int d = p_int(sfp[2]);
    int ret = mpz_fdiv_r_ui(knh_mp,*n,d);

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.mp.fdiv_qr_ui (Gmp q, Gmp r, Gmp n, int d) */

METHOD Gmp_fdivQR2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *r = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *n = (mpz_t*) p_cptr(sfp[2]);
    int d = p_int(sfp[3]);
    int ret = mpz_fdiv_qr_ui(knh_mp,*r,*n,d);

    KNH_RETURN_Int(ctx, sfp, ret);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int    Gmp.mp.fdiv_ui (Gmp n, int d) */

METHOD Gmp_fdiv2(Ctx *ctx, knh_sfp_t* sfp)
{
    int d = p_int(sfp[1]);
    int ret = mpz_fdiv_ui(knh_mp,d);

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void   Gmp.fdiv_q_2exp (Gmp q, Gmp n, int b) */

METHOD Gmp_fdivQ2exp(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    int d = p_int(sfp[2]);
    mpz_fdiv_q_2exp(knh_mp,*n,d);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.fdiv_r_2exp (Gmp r, Gmp n, int b) */

METHOD Gmp_fdivR2exp(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    int d = p_int(sfp[2]);
    mpz_fdiv_r_2exp(knh_mp,*n,d);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.tdiv_q (Gmp q, Gmp n, Gmp d) */

METHOD Gmp_tdivQ(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *d = (mpz_t*) p_cptr(sfp[2]);
    mpz_tdiv_q(knh_mp,*n,*d);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.tdiv_r (Gmp r, Gmp n, Gmp d) */

METHOD Gmp_tdivR(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *d = (mpz_t*) p_cptr(sfp[2]);
    mpz_tdiv_r(knh_mp,*n,*d);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.tdiv_qr (Gmp q, Gmp r, Gmp n, Gmp d) */

METHOD Gmp_tdivQR(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *r = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *n = (mpz_t*) p_cptr(sfp[2]);
    int d = p_int(sfp[3]);
    mpz_tdiv_qr_ui(knh_mp,*r,*n,d);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int    Gmp.tdiv_q_ui (Gmp q, Gmp n, int d) */
METHOD Gmp_tdivQ2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    int d = p_int(sfp[2]);
    int ret = mpz_tdiv_q_ui(knh_mp,*n,d);

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.mpdiv_r_ui (Gmp r, Gmp n, int d) */
METHOD Gmp_tdivR2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[2]);
    int d = p_int(sfp[3]);
    int ret = mpz_tdiv_r_ui(knh_mp,*n,d);

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.tdiv_qr_ui (Gmp q, Gmp r, Gmp n, int d) */
METHOD Gmp_tdivQR2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *r = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *n = (mpz_t*) p_cptr(sfp[2]);
    int d = p_int(sfp[3]);
    int ret = mpz_tdiv_qr_ui(knh_mp,*r,*n,d);

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.tdiv_ui (Gmp n, int d) */
METHOD Gmp_tdiv2(Ctx *ctx, knh_sfp_t* sfp)
{
    int d = p_int(sfp[1]);
    int ret = mpz_tdiv_ui(knh_mp,d);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void   Gmp.tdiv_q_2exp (Gmp q, Gmp n, int b) */

METHOD Gmp_tdivQ2exp(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    int d = p_int(sfp[2]);
    mpz_tdiv_q_2exp(knh_mp,*n,d);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmpdiv_r_2exp (Gmp r, Gmp n, int b) */

METHOD Gmp_tdivR2exp_Gmp(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[1]);
    int d = p_int(sfp[2]);
    mpz_tdiv_r_2exp(knh_mp,*n,d);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.mod (Gmp r, Gmp n, Gmp d) */

METHOD Gmp_mod(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *d = (mpz_t*) p_cptr(sfp[1]);
    mpz_mod(knh_mp,knh_mp,*d);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int    Gmp.mp.mod_ui (Gmp r, Gmp n, int d) */
METHOD Gmp_mod2(Ctx *ctx, knh_sfp_t* sfp)
{
    int d = p_int(sfp[1]);
    int ret = mpz_mod_ui(knh_mp ,knh_mp ,d );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void   Gmp.divexact (Gmp q, Gmp n, Gmp d) */

METHOD Gmp_divexact(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *d = (mpz_t*) p_cptr(sfp[1]);
    mpz_divexact(knh_mp,knh_mp,*d);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.divexact_ui (Gmp q, Gmp n, int d) */

METHOD Gmp_divexact2(Ctx *ctx, knh_sfp_t* sfp)
{
    int d = p_int(sfp[1]);
    mpz_divexact_ui(knh_mp,knh_mp,d);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int    Gmp.divisible_p (Gmp n, Gmp d) */

METHOD Gmp_divisible(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *d = (mpz_t*) p_cptr(sfp[1]);
    int ret = mpz_divisible_p(knh_mp,*d);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.divisible_ui_p (Gmp n, int d) */

METHOD Gmp_divisible2(Ctx *ctx, knh_sfp_t* sfp)
{
    int d = p_int(sfp[1]);
    int ret = mpz_divisible_ui_p(knh_mp ,d );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.divisible_2exp_p (Gmp n, int b) */

METHOD Gmp_divisible2exp(Ctx *ctx, knh_sfp_t* sfp)
{
    int d = p_int(sfp[1]);
    int ret = mpz_divisible_2exp_p(knh_mp ,d );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.congruent_p (Gmp n, Gmp c, Gmp d) */

METHOD Gmp_congurent(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *c = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *d = (mpz_t*) p_cptr(sfp[2]);
    int ret = mpz_congruent_p(knh_mp ,*c,*d );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.congruent_ui_p (Gmp n, int c, int d) */

METHOD Gmp_congurent2(Ctx *ctx, knh_sfp_t* sfp)
{
    int c = p_int(sfp[1]);
    int d = p_int(sfp[2]);
    int ret = mpz_congruent_ui_p(knh_mp ,c,d );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.mp.congruent_2exp_p (Gmp n, Gmp c, int b) */

METHOD Gmp_congurent2exp(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *c = (mpz_t*) p_cptr(sfp[1]);
    int d = p_int(sfp[2]);
    int ret = mpz_congruent_2exp_p(knh_mp ,*c,d );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void   Gmp.powm (Gmp rop, Gmp base, Gmp exp, Gmp mod) */

METHOD Gmp_powm(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *base = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *exp  = (mpz_t*) p_cptr(sfp[2]);
    mpz_t *mod  = (mpz_t*) p_cptr(sfp[3]);
    mpz_powm(knh_mp,*base,*exp,*mod);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.powm_ui (Gmp rop, Gmp base, int exp, Gmp mod) */
METHOD Gmp_powm2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *base = (mpz_t*) p_cptr(sfp[1]);
    int exp = p_int(sfp[2]);
    mpz_t *mod  = (mpz_t*) p_cptr(sfp[3]);
    mpz_powm_ui(knh_mp,*base,exp,*mod);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.pow_ui (Gmp rop, Gmp base, int exp) */
METHOD Gmp_pow2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *base = (mpz_t*) p_cptr(sfp[1]);
    int exp = p_int(sfp[2]);
    mpz_pow_ui(knh_mp,*base,exp);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.ipow2 (Gmp rop, int base, int exp) */

METHOD Gmp_ipow2(Ctx *ctx, knh_sfp_t* sfp)
{
    int base = p_int(sfp[1]);
    int exp = p_int(sfp[2]);
    mpz_ui_pow_ui(knh_mp,base,exp);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int    Gmp.root (Gmp rop, Gmp op, int n) */
METHOD Gmp_root(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op = (mpz_t*) p_cptr(sfp[1]);
    int n = p_int(sfp[2]);
    int ret = mpz_root(knh_mp ,*op ,n );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void   Gmp.rootrem (Gmp root, Gmp rem, Gmp u, int n) */

METHOD Gmp_rootrem(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *rem = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *u = (mpz_t*) p_cptr(sfp[2]);
    int n = p_int(sfp[3]);
    mpz_rootrem(knh_mp,*rem,*u,n);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.sqrt (Gmp rop, Gmp op) */

METHOD Gmp_sqrt(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op = (mpz_t*) p_cptr(sfp[1]);
    mpz_sqrt(knh_mp,*op);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.sqrtrem (Gmp rop1, Gmp rop2, Gmp op) */

METHOD Gmp_sqrtrem(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *op2 = (mpz_t*) p_cptr(sfp[2]);
    mpz_sqrtrem(knh_mp,*op1,*op2);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int    Gmp.perfectPower (Gmp op) */
METHOD Gmp_perfectPower(Ctx *ctx, knh_sfp_t* sfp)
{
    int ret = mpz_perfect_power_p(knh_mp);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.mp.perfect_square (Gmp op) */
METHOD Gmp_perfectSquare(Ctx *ctx, knh_sfp_t* sfp)
{
    int ret = mpz_perfect_square_p(knh_mp);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.probab_prime_p (Gmp n, int reps) */

METHOD Gmp_probabPrime(Ctx *ctx, knh_sfp_t* sfp)
{
    int reps = p_int(sfp[1]);
    int ret  = mpz_probab_prime_p(knh_mp,reps );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void   Gmp.nextprime (Gmp rop, Gmp op) */

METHOD Gmp_nextprime(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op = (mpz_t*) p_cptr(sfp[1]);
    mpz_nextprime(knh_mp,*op);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.gcd (Gmp rop, Gmp op1, Gmp op2) */
METHOD Gmp_gcd(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *op2 = (mpz_t*) p_cptr(sfp[2]);
    mpz_gcd(knh_mp,*op1,*op2);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int    Gmp.mp.gcd_ui (Gmp rop, Gmp op1, int op2) */
METHOD Gmp_gcd2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    int op2 = p_int(sfp[2]);
    int ret = mpz_gcd_ui(knh_mp ,*op1 ,op2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void   Gmp.gcdext (Gmp g, Gmp s, Gmp t, Gmp a, Gmp b) */
METHOD Gmp_gcdext(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *s = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *t = (mpz_t*) p_cptr(sfp[2]);
    mpz_t *a = (mpz_t*) p_cptr(sfp[3]);
    mpz_t *b = (mpz_t*) p_cptr(sfp[4]);
    mpz_gcdext(knh_mp,*s,*t,*a,*b);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.lcm (Gmp rop, Gmp op1, Gmp op2) */
METHOD Gmp_lcm(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *op2 = (mpz_t*) p_cptr(sfp[2]);
    mpz_lcm(knh_mp,*op1,*op2);
    KNH_RETURN(ctx,sfp,sfp[0].o);

}

/* void   Gmp.lcm_ui (Gmp rop, Gmp op1, int op2) */
METHOD Gmp_lcm2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    int op2 = p_int(sfp[2]);
    mpz_lcm_ui(knh_mp,*op1,op2);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int    Gmp.invert (Gmp rop, Gmp op1, Gmp op2) */
METHOD Gmp_invert(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *op2 = (mpz_t*) p_cptr(sfp[2]);
    int ret = mpz_invert(knh_mp,*op1,*op2);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.jacobi (Gmp a, Gmp b) */

METHOD Gmp_jacobi(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *b = (mpz_t*) p_cptr(sfp[1]);
    int ret = mpz_jacobi(knh_mp,*b);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.legendre (Gmp a, Gmp p) */

METHOD Gmp_legendre(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *p = (mpz_t*) p_cptr(sfp[1]);
    int ret = mpz_legendre(knh_mp,*p);

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.kronecker (Gmp a, Gmp b) */
METHOD Gmp_kronecker(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *b = (mpz_t*) p_cptr(sfp[1]);
    int ret = mpz_kronecker(knh_mp ,*b );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.kronecker_ui (Gmp a, int b) */
METHOD Gmp_kronecker2(Ctx *ctx, knh_sfp_t* sfp)
{
    int b   = p_int(sfp[1]);
    int ret = mpz_kronecker_ui(knh_mp ,b );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.intKronecker (int a, Gmp b) */
METHOD Gmp_intKronecker(Ctx *ctx, knh_sfp_t* sfp)
{
    int a   = p_int(sfp[1]);
    int ret = mpz_ui_kronecker(a ,knh_mp );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.remove (Gmp rop, Gmp op, Gmp f) */

METHOD Gmp_remove(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *f  = (mpz_t*) p_cptr(sfp[2]);
    int ret = mpz_remove(knh_mp,*op,*f);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void   Gmp.fac_ui (Gmp rop, int op) */

METHOD Gmp_fac(Ctx *ctx, knh_sfp_t* sfp)
{
    int op = p_int(sfp[1]);
    mpz_fac_ui(knh_mp,op);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.bin_ui (Gmp rop, Gmp n, int k) */

METHOD Gmp_bin(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n  = (mpz_t*) p_cptr(sfp[1]);
    int k = p_int(sfp[2]);
    mpz_bin_ui(knh_mp,*n,k);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.bin_uiui (Gmp rop, int n, int k) */

METHOD Gmp_bin2(Ctx *ctx, knh_sfp_t* sfp)
{
    int n = p_int(sfp[1]);
    int k = p_int(sfp[2]);
    mpz_bin_uiui(knh_mp,n,k);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.fib_ui (Gmp fn, int n) */

METHOD Gmp_fib(Ctx *ctx, knh_sfp_t* sfp)
{
    int n = p_int(sfp[1]);
    mpz_fib_ui(knh_mp,n);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.fib2_ui (Gmp fn, Gmp fnsub1, int n) */

METHOD Gmp_fib2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *fnsub1 = (mpz_t*) p_cptr(sfp[1]);
    int n = p_int(sfp[2]);
    mpz_fib2_ui(knh_mp,*fnsub1,n);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.lucnum_ui (Gmp ln, int n) */

METHOD Gmp_lucnum(Ctx *ctx, knh_sfp_t* sfp)
{
    int n = p_int(sfp[1]);
    mpz_lucnum_ui(knh_mp,n);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.lucnum2_ui (Gmp ln, Gmp lnsub1, int n) */

METHOD Gmp_lucnum2(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *lnsub1 = (mpz_t*) p_cptr(sfp[1]);
    int n = p_int(sfp[2]);
    mpz_lucnum2_ui(knh_mp,*lnsub1,n);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int    Gmp.cmp (Gmp op1, Gmp op2) */

METHOD Gmp_cmp(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op = (mpz_t*) p_cptr(sfp[1]);
    int ret = mpz_cmp(knh_mp,*op );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.mp.cmp_d (Gmp op1, float op2) */

METHOD Gmp_cmpDouble(Ctx *ctx, knh_sfp_t* sfp)
{
    double op = (double) p_float(sfp[1]);
    int ret = mpz_cmp_d(knh_mp,op);

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.mp.cmp_ui (Gmp op1, int op2) */

METHOD Gmp_cmpInt(Ctx *ctx, knh_sfp_t* sfp)
{
    int op  = p_int(sfp[1]);
    int ret = mpz_cmp_ui(knh_mp,op );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.mp.cmpabs (Gmp op1, Gmp op2) */

METHOD Gmp_cmpAbs(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op = (mpz_t*) p_cptr(sfp[1]);
    int ret = mpz_cmpabs(knh_mp,*op);

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.mp.cmpabs_d (Gmp op1, float op2) */

METHOD Gmp_cmpAbsDouble(Ctx *ctx, knh_sfp_t* sfp)
{
    double op = (double) p_float(sfp[1]);
    int ret = mpz_cmpabs_d(knh_mp,op);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.mp.cmpabs_ui (Gmp op1, int op2) */

METHOD Gmp_cmpAbsInt(Ctx *ctx, knh_sfp_t* sfp)
{
    int op  = p_int(sfp[1]);
    int ret = mpz_cmpabs_ui(knh_mp,op );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void   Gmp.and (Gmp rop, Gmp op1, Gmp op2) */

METHOD Gmp_and(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *op2 = (mpz_t*) p_cptr(sfp[2]);
    mpz_add(knh_mp,*op1,*op2);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.ior (Gmp rop, Gmp op1, Gmp op2) */

METHOD Gmp_ior(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *op2 = (mpz_t*) p_cptr(sfp[2]);
    mpz_ior(knh_mp,*op1,*op2);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.xor (Gmp rop, Gmp op1, Gmp op2) */

METHOD Gmp_xor(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op1 = (mpz_t*) p_cptr(sfp[1]);
    mpz_t *op2 = (mpz_t*) p_cptr(sfp[2]);
    mpz_xor(knh_mp,*op1,*op2);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.com (Gmp rop, Gmp op) */

METHOD Gmp_com(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op = (mpz_t*) p_cptr(sfp[1]);
    mpz_com(knh_mp,*op);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int    Gmp.popcount (Gmp op) */

METHOD Gmp_popcount(Ctx *ctx, knh_sfp_t* sfp)
{
    int ret = mpz_popcount(knh_mp );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.hamdist (Gmp op1, Gmp op2) */
METHOD Gmp_hamdist(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op = (mpz_t*) p_cptr(sfp[1]);
    int ret = mpz_hamdist(knh_mp,*op );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.scan0 (Gmp op, int starting_bit) */
METHOD Gmp_scan0(Ctx *ctx, knh_sfp_t* sfp)
{
    int bit = p_int(sfp[1]);
    int ret = mpz_scan0(knh_mp,bit);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.scan1 (Gmp op, int starting_bit) */
METHOD Gmp_scan1(Ctx *ctx, knh_sfp_t* sfp)
{
    int bit = p_int(sfp[1]);
    int ret = mpz_scan1(knh_mp,bit);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void   Gmp.setbit (Gmp rop, int bit_index) */

METHOD Gmp_setbit(Ctx *ctx, knh_sfp_t* sfp)
{
    int bit_index = p_int(sfp[1]);
    mpz_setbit(knh_mp,bit_index);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.clrbit (Gmp rop, int bit_index) */

METHOD Gmp_clrbit(Ctx *ctx, knh_sfp_t* sfp)
{
    int bit_index = p_int(sfp[1]);
    mpz_clrbit(knh_mp,bit_index);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void   Gmp.combit (Gmp rop, int bit_index) */

METHOD Gmp_combit(Ctx *ctx, knh_sfp_t* sfp)
{
    int bit_index = p_int(sfp[1]);
    mpz_combit(knh_mp,bit_index);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int    Gmp.tstbit (Gmp op, int bit_index) */

METHOD Gmp_mpstbit(Ctx *ctx, knh_sfp_t* sfp)
{
    int bit_index = p_int(sfp[1]);
    int ret = mpz_tstbit(knh_mp ,bit_index );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int Gmp.outStr (FILE *stream, int base, Gmp op) */
/*
METHOD Gmp_out_str(Ctx *ctx, knh_sfp_t* sfp)
{
    FILE* stream = (FILE*) p_cptr(sfp[1]);
    int base = p_int(sfp[2]);
    mpz_t *op = (mpz_t*) p_cptr(sfp[3]);
    int ret = mpz_out_str(*stream ,base ,*op );

    KNH_RETURN_Int(ctx, sfp, ret);
}
*/

/* int Gmp.inp_str (Gmp rop, FILE *stream, int base) */
/*
METHOD Gmp_inp_str(Ctx *ctx, knh_sfp_t* sfp)
{
    FILE* stream = (FILE*) p_cptr(sfp[1]);
    int base = p_int(sfp[2]);
    int ret = mpz_inp_str(knh_mp ,*stream ,base );
    KNH_RETURN_Int(ctx, sfp, ret);
}
*/

/* int Gmp.out_raw (FILE *stream, Gmp op) */
/*
METHOD Gmp_out_raw(Ctx *ctx, knh_sfp_t* sfp)
{
    FILE* stream = (FILE*) p_cptr(sfp[1]);
    mpz_t *op = (mpz_t*) p_cptr(sfp[2]);
    int ret = mpz_out_raw(*stream ,*op );

    KNH_RETURN_Int(ctx, sfp, ret);
}
*/

/* int Gmp.inp_raw (Gmp rop, FILE *stream) */
/*
METHOD Gmp_inp_raw(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *op = (mpz_t*) p_cptr(sfp[1]);
    FILE* stream = (FILE*) p_cptr(sfp[2]);
    int ret = mpz_inp_raw(*op ,*stream );

    KNH_RETURN_Int(ctx, sfp, ret);
}
*/

/* void  Gmp.urandomb (Gmp rop, gmp_randstate_t state, int n) */
/*
METHOD Gmp_urandomb(Ctx *ctx, knh_sfp_t* sfp)
{
    int n = p_int(sfp[2]);
    mpz_uranddomb(knh_mp,state,n);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}
*/

/* void  Gmp.urandomm (Gmp rop, gmp_randstate_t state, Gmp n) */
/*
METHOD Gmp_urandomm(Ctx *ctx, knh_sfp_t* sfp)
{
    mpz_t *n = (mpz_t*) p_cptr(sfp[2]);
    mpz_uranddomm(knh_mp,state,*n);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}
*/

/* void  Gmp.rrandomb (Gmp rop, gmp_randstate_t state, int n) */
/*
METHOD Gmp_rrandomb(Ctx *ctx, knh_sfp_t* sfp)
{
    int n = p_int(sfp[2]);
    mpz_rranddomb(knh_mp,state,n);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}
*/

/* void   Gmp.random (Gmp rop, mp_int max_size) */
/*
METHOD Gmp_random(Ctx *ctx, knh_sfp_t* sfp)
{
    int n = p_int(sfp[2]);

    KNH_RETURN(ctx,sfp,sfp[0].o);
}
*/
/* void   Gmp.random2 (Gmp rop, mp_int max_size) */
/*
METHOD Gmp_random2(Ctx *ctx, knh_sfp_t* sfp)
{

    KNH_RETURN(ctx,sfp,sfp[0].o);
    KNH_RETURN_void(ctx, sfp);
}
*/


/* int    Gmp.mp.fits_int_p (Gmp op) */

METHOD Gmp_fitsInt(Ctx *ctx, knh_sfp_t* sfp)
{
    int ret = mpz_fits_uint_p(knh_mp);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.mp.odd_p (Gmp op) */

METHOD Gmp_odd(Ctx *ctx, knh_sfp_t* sfp)
{
    int ret = mpz_odd_p(knh_mp);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int    Gmp.mp.even_p (Gmp op) */

METHOD Gmp_even(Ctx *ctx, knh_sfp_t* sfp)
{
    int ret = mpz_even_p(knh_mp);
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int Gmp.sizeinbase (Gmp op, int base) */

METHOD Gmp_sizeinbase(Ctx *ctx, knh_sfp_t* sfp)
{
    int base = p_int(sfp[1]);
    int ret = mpz_sizeinbase(knh_mp ,base );
    KNH_RETURN_Int(ctx, sfp, ret);
}

/* int Gmp.getlimbn (Gmp op, mp_int n) */
/*
METHOD Gmp_getlimbn(Ctx *ctx, knh_sfp_t* sfp)
{
    int ret = GmpGetlimbn(op ,n );

    KNH_RETURN_Int(ctx, sfp, ret);
}
*/
/* int Gmp.size (Gmp op) */
/*
METHOD Gmp_size(Ctx *ctx, knh_sfp_t* sfp)
{
    int ret = GmpSize(op );

    KNH_RETURN_Int(ctx, sfp, ret);
}

*/
