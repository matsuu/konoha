#include <konoha.h>
#include <oniguruma.h>

regex_t* knh_onig_reg;
OnigErrorInfo knh_onig_einfo;
OnigRegion* knh_onig_region;

METHOD Onig_compile(Ctx *ctx,knh_sfp_t *sfp){
    int r;
    unsigned char* pattern = (unsigned char*)p_char(sfp[1]);
    printf("pattern %s\n",pattern);
    r = onig_new(&knh_onig_reg, pattern,
            pattern + strlen((char* )pattern),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8,
            ONIG_SYNTAX_DEFAULT, &knh_onig_einfo);
    if (r != ONIG_NORMAL) {
        char s[ONIG_MAX_ERROR_MESSAGE_LEN];
        onig_error_code_to_str(s, r, &knh_onig_einfo);
        fprintf(stderr, "r:ERROR: %s\n", s);
        KNH_RETURN(ctx,sfp,sfp[0].o);
    }

    KNH_RETURN(ctx,sfp,sfp[0].o);
}
METHOD Onig_match(Ctx *ctx,knh_sfp_t *sfp){
    int r;
    unsigned char *start,*range,*end;
    unsigned char* str = (unsigned char*)p_char(sfp[1]);

    if(knh_onig_reg == NULL) {
        KNH_RETURN(ctx,sfp,sfp[0].o);
    }
    end   = str + strlen((char* )str);
    start = str;
    range = end;
    knh_onig_region = onig_region_new();
    r = onig_search(knh_onig_reg, str, end,start,
            range, knh_onig_region, ONIG_OPTION_NONE);

    if (r >= 0) {
        int i;
        fprintf(stderr, "match at %d\n", r);
        for (i = 0; i < knh_onig_region->num_regs; i++) {
            fprintf(stderr, "%d: (%d-%d)\n", i,
                    knh_onig_region->beg[i],
                    knh_onig_region->end[i]);
        }
    } else if (r == ONIG_MISMATCH) {
        fprintf(stderr, "search fail\n");
    } else { /* error */
        char s[ONIG_MAX_ERROR_MESSAGE_LEN];
        onig_error_code_to_str(s, r);
        fprintf(stderr, "i:ERROR: %s\n", s);
        KNH_RETURN(ctx,sfp,sfp[0].o);
    }
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

