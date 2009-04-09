#include <time.h>
#include <konoha.h>

METHOD Time_new(Ctx *ctx,knh_sfp_t *sfp){
    time_t timer;
    struct tm *date;

    /* 現在の日時を取得 */
    time(&timer);
    date = localtime(&timer);

    date->tm_year = date->tm_year + 1900;
    date->tm_mon  = date->tm_mon  + 1;
    knh_Glue_init(ctx,sfp[0].glue,date,NULL);//knh_time_gfree);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}
METHOD Time_setTime(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int year  = p_int(sfp[1]);
    int month = p_int(sfp[2]);
    int day   = p_int(sfp[3]);
    int hour  = p_int(sfp[4]);
    int min   = p_int(sfp[5]);
    int sec   = p_int(sfp[6]);

    date->tm_year = year;
    date->tm_mon  = month;
    date->tm_mday = day;
    date->tm_hour = hour;
    date->tm_min  = min;
    date->tm_sec  = sec;
    KNH_RETURN_void(ctx,sfp);
}
METHOD Time_getYear(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int year  = date->tm_year;
    KNH_RETURN_Int(ctx,sfp,year);
}
METHOD Time_getMonth(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int month = date->tm_mon;
    KNH_RETURN_Int(ctx,sfp,month);
}
METHOD Time_getDay(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int day   = date->tm_mday;
    KNH_RETURN_Int(ctx,sfp,day);
}

METHOD Time_getHour(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int hour  = date->tm_hour;
    KNH_RETURN_Int(ctx,sfp,hour);
}
METHOD Time_getMinute(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int min   = date->tm_min;
    KNH_RETURN_Int(ctx,sfp,min);
}

METHOD Time_getSecond(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int sec   = date->tm_sec;
    KNH_RETURN_Int(ctx,sfp,sec);
}

