#include <time.h>
#include <konoha.h>

/* Time! Time.new(); */
METHOD Time_new(Ctx *ctx,knh_sfp_t *sfp){
    time_t timer;
    struct tm *date;

    /* 現在の日時を取得 */
    time(&timer);
    date = localtime(&timer);

    date->tm_year = date->tm_year;
    date->tm_mon  = date->tm_mon;
    knh_Glue_init(ctx,sfp[0].glue,date,NULL);//knh_time_gfree);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* void Time.mktime(Time time); */
METHOD Time_mktime(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    struct tm *time = (struct tm*)p_cptr(sfp[1]);
    time_t timer;
    timer = mktime(time);
    date = localtime(&timer);
    KNH_RETURN_void(ctx,sfp);

}
/* string Time.ctime() */
METHOD Time_asctime(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    char* ret = asctime(date);
    KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* Time! Time.gmtime() */
METHOD Time_gmtime(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    time_t timer;
    timer = mktime(date);
    date = gmtime(&timer);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* Time! Time.localtime() */
/*
METHOD Time_localtime(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    date = localtime(date);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}
*/

/* void Time.setTime(int year,int month,int day,int hour,int min,int sec); */
METHOD Time_setTime(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int year  = p_int(sfp[1]);
    int month = p_int(sfp[2]);
    int day   = p_int(sfp[3]);
    int hour  = p_int(sfp[4]);
    int min   = p_int(sfp[5]);
    int sec   = p_int(sfp[6]);

    date->tm_year = year - 1900;
    date->tm_mon  = month -1;
    date->tm_mday = day;
    date->tm_hour = hour;
    date->tm_min  = min;
    date->tm_sec  = sec;
    KNH_RETURN_void(ctx,sfp);
}

/* int Time.getYear() */
METHOD Time_getYear(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int year  = date->tm_year+1900;
    KNH_RETURN_Int(ctx,sfp,year);
}

/* int Time.getMonth() */
METHOD Time_getMonth(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int month = date->tm_mon+1;
    KNH_RETURN_Int(ctx,sfp,month);
}

/* int Time.getDay() */
METHOD Time_getDay(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int day   = date->tm_mday;
    KNH_RETURN_Int(ctx,sfp,day);
}

/* int Time.getHour() */
METHOD Time_getHour(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int hour  = date->tm_hour;
    KNH_RETURN_Int(ctx,sfp,hour);
}
/* int Time.getMinute() */
METHOD Time_getMinute(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int min   = date->tm_min;
    KNH_RETURN_Int(ctx,sfp,min);
}

/* int Time.getSecond() */
METHOD Time_getSecond(Ctx *ctx,knh_sfp_t *sfp){
    struct tm *date = (struct tm*)p_cptr(sfp[0]);
    int sec   = date->tm_sec;
    KNH_RETURN_Int(ctx,sfp,sec);
}

