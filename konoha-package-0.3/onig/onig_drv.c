#include <konoha.h>
#include <oniguruma.h>

knh_regex_t* knh_onig_malloc(Ctx *ctx)
{
    return (regex_t*) KNH_MALLOC(ctx,sizeof(regex_t));
}

void knh_onig_regfree(Ctx *ctx, knh_regex_t *reg)
{
    onig_free((regex_t*)reg);
    //onig_end();
    KNH_FREE(ctx,reg,sizeof(regex_t));
}

int knh_onig_regcomp(Ctx *ctx,knh_regex_t *reg, char *pattern,int flags)
{
    regex_t* r = (regex_t*)reg;
    OnigErrorInfo einfo;
    printf("pattern %s\n",pattern);
    int res = onig_new(&r, (UChar*)pattern,
            (UChar*) pattern + strlen(pattern),
            ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8,
            ONIG_SYNTAX_DEFAULT, &einfo);
    if (res != ONIG_NORMAL) {
        char buf[ONIG_MAX_ERROR_MESSAGE_LEN];
        onig_error_code_to_str(buf, res, &einfo);
        KNH_WARNING(ctx, "onig_regex(ERROR): %s", buf);
    }

    return res;

}

int knh_onig_regexec(Ctx *ctx,knh_regex_t *reg, char *str,size_t nmatch,
        knh_regmatch_t p[], int flags)
{
    UChar* ustr  = (UChar*) str;
    UChar* end   = ustr + strlen(str);
    UChar* start = ustr;
    UChar* range = end;
    OnigRegion* region = onig_region_new();

    int res = onig_search((regex_t*) reg, ustr, end, start,
            range, region, ONIG_OPTION_NONE);

    if (res >= 0) {
        size_t i;
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
    return res;
}

static knh_regex_drvapi_t RE__onig = {
    KNH_DRVAPI_TYPE__REGEX, 
    "onig", // ドライバー名
    knh_onig_malloc, // 作成した関数
    knh_onig_regcomp, 
    knh_onig_regexec,
    knh_onig_regfree
};

int init(Ctx *ctx){
    onig_init();
    konoha_addRegexDriver(ctx, "onig", &RE__onig);
    konoha_addRegexDriver(ctx, "re", &RE__onig);
    return 0;
}
