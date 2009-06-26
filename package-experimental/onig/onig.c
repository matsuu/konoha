#include <konoha.h>
#include <oniguruma.h>

METHOD Onig_compile(Ctx *ctx,knh_sfp_t *sfp){
    regex_t* reg = (regex_t *) p_cptr(sfp[0]);
    unsigned char* pattern = (unsigned char*)p_char(sfp[1]);
    OnigErrorInfo errinfo;
    int res = onig_new(&reg, pattern,
            pattern + strlen((char* )pattern),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8,
            ONIG_SYNTAX_DEFAULT, &errinfo);
    printf("pattern %s\n",pattern);
    if (res != ONIG_NORMAL) {
        char buf[ONIG_MAX_ERROR_MESSAGE_LEN];
        onig_error_code_to_str(buf, res, &errinfo);
        KNH_WARNING(ctx, "onig_regex(ERROR): %s", buf);
    }

    KNH_RETURN(ctx,sfp,sfp[0].o);
}
METHOD Onig_match(Ctx *ctx,knh_sfp_t *sfp){
    OnigRegion* region;
    unsigned char *start,*range,*end;
    regex_t* reg = (regex_t *) p_cptr(sfp[0]);
    unsigned char* str = (unsigned char*)p_char(sfp[1]);
    int res;

    if(reg == NULL) {
        KNH_WARNING(ctx, "onig_regex(ERROR): do compile!");
    }

    end   = str + strlen((char* )str);
    start = str;
    range = end;
    region = onig_region_new();
    res = onig_search(reg, str, end,start,
            range, region, ONIG_OPTION_NONE);

    if (res >= 0) {
        int i;
        fprintf(stderr, "match at %d\n", res);
        for (i = 0; i < region->num_regs; i++) {
            fprintf(stderr, "%d: (%d-%d)\n", i,
                    region->beg[i],
                    region->end[i]);
        }
    } else if (res == ONIG_MISMATCH) {
        fprintf(stderr, "search fail\n");
    } else if(res < 0){ /* error */
        char buf[ONIG_MAX_ERROR_MESSAGE_LEN];
        onig_error_code_to_str(buf, res);
        KNH_WARNING(ctx, "onig_regex(ERROR): %s", buf);
    }
    onig_region_free(region,1); /* 1:free self, 0:free contents only */
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

