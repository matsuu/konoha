#include <konoha.h>
#include <ncurses.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Int Curses.box(self, Int i1, Int i2) */

METHOD Curses_box(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = box(self ,i1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.clearok(self, Boolean b1) */

METHOD Curses_clearok(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int b1 = p_int(sfp[1]);
    int ret = clearok(self ,b1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.delwin(self) */

METHOD Curses_delwin(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = delwin(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Curses Curses.derwin(self, Int i1, Int i2, Int i3, Int i4) */

METHOD Curses_derwin(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int i3 = p_int(sfp[3]);
    int i4 = p_int(sfp[4]);
    WINDOW *ret = derwin(self ,i1 ,i2 ,i3 ,i4 );

    KNH_RETURN(ctx, sfp, ret);
}

/* Curses Curses.dupwin(self) */

METHOD Curses_dupwin(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    WINDOW *ret = dupwin(self );

    KNH_RETURN(ctx, sfp, ret);
}

/* void Curses.endwin(self) */

METHOD Curses_endwin(Ctx *ctx, knh_sfp_t* sfp)
{
    endwin();
    KNH_RETURN_void(ctx, sfp);;
}


/* Int Curses.getbkgd(self) */

METHOD Curses_getbkgd(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = getbkgd(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void Curses.idcok(self, Boolean b1) */

METHOD Curses_idcok(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int b1 = p_int(sfp[1]);
    idcok(self ,b1 );

    KNH_RETURN_void(ctx, sfp);
}

/* Int Curses.idlok(self, Boolean b1) */

METHOD Curses_idlok(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int b1 = p_int(sfp[1]);
    int ret = idlok(self ,b1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void Curses.immedok(self, Boolean b1) */

METHOD Curses_immedok(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int b1 = p_int(sfp[1]);
    immedok(self ,b1 );

    KNH_RETURN_void(ctx, sfp);
}

/* Curses Curses.initscr() */

METHOD Curses_initscr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW* ret = initscr();
    KNH_RETURN(ctx, sfp, ret);
}

/* Int Curses.intrflush(self, Boolean b1) */

METHOD Curses_intrflush(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int b1 = p_int(sfp[1]);
    int ret = intrflush(self ,b1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Boolean Curses.isLinetouched(self, Int i1) */

METHOD Curses_isLinetouched(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int ret = is_linetouched(self ,i1 );

    KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean Curses.isWintouched(self) */

METHOD Curses_isWintouched(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = is_wintouched(self );

    KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Int Curses.keypad(self, Boolean b1) */

METHOD Curses_keypad(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int b1 = p_int(sfp[1]);
    int ret = keypad(self ,b1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.leaveok(self, Boolean b1) */

METHOD Curses_leaveok(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int b1 = p_int(sfp[1]);
    int ret = leaveok(self ,b1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.meta(self, Boolean b1) */

METHOD Curses_meta(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int b1 = p_int(sfp[1]);
    int ret = meta(self ,b1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvderwin(self, Int i1, Int i2) */

METHOD Curses_mvderwin(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = mvderwin(self ,i1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwaddch(self, Int i1, Int i2, Int i3) */

METHOD Curses_mvwaddch(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    char* i3 = p_char(sfp[3]);
    int ret = mvwaddch(self ,i1 ,i2 ,*i3 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwaddnstr(self, Int i1, Int i2, String s3, Int i4) */

METHOD Curses_mvwaddnstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    char *s3 = p_char(sfp[3]);
    int i4 = p_int(sfp[4]);
    int ret = mvwaddnstr(self ,i1 ,i2 ,s3 ,i4 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwaddstr(self, Int i1, Int i2, String s3) */

METHOD Curses_mvwaddstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    char *s3 = p_char(sfp[3]);
    int ret = mvwaddstr(self ,i1 ,i2 ,s3 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwdelch(self, Int i1, Int i2) */

METHOD Curses_mvwdelch(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = mvwdelch(self ,i1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwgetch(self, Int i1, Int i2) */

METHOD Curses_mvwgetch(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = mvwgetch(self ,i1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwgetnstr(self, Int i1, Int i2, String s3, Int i4) */

METHOD Curses_mvwgetnstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    char *s3 = p_char(sfp[3]);
    int i4 = p_int(sfp[4]);
    int ret = mvwgetnstr(self ,i1 ,i2 ,s3 ,i4 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwgetstr(self, Int i1, Int i2, String s3) */

METHOD Curses_mvwgetstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    char *s3 = p_char(sfp[3]);
    int ret = mvwgetstr(self ,i1 ,i2 ,s3 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwhline(self, Int i1, Int i2, Int i3, Int i4) */

METHOD Curses_mvwhline(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int i3 = p_int(sfp[3]);
    int i4 = p_int(sfp[4]);
    int ret = mvwhline(self ,i1 ,i2 ,i3 ,i4 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwin(self, Int i1, Int i2) */

METHOD Curses_mvwin(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = mvwin(self ,i1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwinch(self, Int i1, Int i2) */

METHOD Curses_mvwinch(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = mvwinch(self ,i1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwinnstr(self, Int i1, Int i2, String s3, Int i4) */

METHOD Curses_mvwinnstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    char *s3 = p_char(sfp[3]);
    int i4 = p_int(sfp[4]);
    int ret = mvwinnstr(self ,i1 ,i2 ,s3 ,i4 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwinsch(self, Int i1, Int i2, Int i3) */

METHOD Curses_mvwinsch(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int i3 = p_int(sfp[3]);
    int ret = mvwinsch(self ,i1 ,i2 ,i3 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwinsnstr(self, Int i1, Int i2, String s3, Int i4) */

METHOD Curses_mvwinsnstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    char *s3 = p_char(sfp[3]);
    int i4 = p_int(sfp[4]);
    int ret = mvwinsnstr(self ,i1 ,i2 ,s3 ,i4 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwinsstr(self, Int i1, Int i2, String s3) */

METHOD Curses_mvwinsstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    char *s3 = p_char(sfp[3]);
    int ret = mvwinsstr(self ,i1 ,i2 ,s3 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwinstr(self, Int i1, Int i2, String s3) */

METHOD Curses_mvwinstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    char *s3 = p_char(sfp[3]);
    int ret = mvwinstr(self ,i1 ,i2 ,s3 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.mvwvline(self, Int i1, Int i2, Int i3, Int i4) */

METHOD Curses_mvwvline(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int i3 = p_int(sfp[3]);
    int i4 = p_int(sfp[4]);
    int ret = mvwvline(self ,i1 ,i2 ,i3 ,i4 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.nodelay(self, Boolean b1) */

METHOD Curses_nodelay(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int b1 = p_int(sfp[1]);
    int ret = nodelay(self ,b1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.notimeout(self, Boolean b1) */

METHOD Curses_notimeout(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int b1 = p_int(sfp[1]);
    int ret = notimeout(self ,b1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.pechochar(self, Int i1) */

METHOD Curses_pechochar(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int ret = pechochar(self ,i1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.pnoutrefresh(self, Int i1, Int i2, Int i3, Int i4, Int i5, Int i6) */

METHOD Curses_pnoutrefresh(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int i3 = p_int(sfp[3]);
    int i4 = p_int(sfp[4]);
    int i5 = p_int(sfp[5]);
    int i6 = p_int(sfp[6]);
    int ret = pnoutrefresh(self ,i1 ,i2 ,i3 ,i4 ,i5 ,i6 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.prefresh(self, Int i1, Int i2, Int i3, Int i4, Int i5, Int i6) */

METHOD Curses_prefresh(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int i3 = p_int(sfp[3]);
    int i4 = p_int(sfp[4]);
    int i5 = p_int(sfp[5]);
    int i6 = p_int(sfp[6]);
    int ret = prefresh(self ,i1 ,i2 ,i3 ,i4 ,i5 ,i6 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.redrawwin(self) */

METHOD Curses_redrawwin(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = redrawwin(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.scroll(self) */

METHOD Curses_scroll(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = scroll(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.scrollok(self, Boolean b1) */

METHOD Curses_scrollok(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int b1 = p_int(sfp[1]);
    int ret = scrollok(self ,b1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Curses Curses.subpad(self, Int i1, Int i2, Int i3, Int i4) */

METHOD Curses_subpad(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int i3 = p_int(sfp[3]);
    int i4 = p_int(sfp[4]);
    WINDOW *ret = subpad(self ,i1 ,i2 ,i3 ,i4 );

    KNH_RETURN(ctx, sfp, ret);
}

/* Curses Curses.subwin(self, Int i1, Int i2, Int i3, Int i4) */

METHOD Curses_subwin(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int i3 = p_int(sfp[3]);
    int i4 = p_int(sfp[4]);
    WINDOW *ret = subwin(self ,i1 ,i2 ,i3 ,i4 );

    KNH_RETURN(ctx, sfp, ret);
}

/* Int Curses.syncok(self, Boolean b1) */

METHOD Curses_syncok(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int b1 = p_int(sfp[1]);
    int ret = syncok(self ,b1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.touchline(self, Int i1, Int i2) */

METHOD Curses_touchline(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = touchline(self ,i1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.touchwin(self) */

METHOD Curses_touchwin(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = touchwin(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.untouchwin(self) */

METHOD Curses_untouchwin(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = untouchwin(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.waddch(self, Int i1) */

METHOD Curses_waddch(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int ret = waddch(self ,i1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.waddnstr(self, String s1, Int i2) */

METHOD Curses_waddnstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    char *s1 = p_char(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = waddnstr(self ,s1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.waddstr(self, String s1) */

METHOD Curses_waddstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    char *s1 = p_char(sfp[1]);
    int ret = waddstr(self ,s1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wattron(self, Int i1) */

METHOD Curses_wattron(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int ret = wattron(self ,i1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wattroff(self, Int i1) */

METHOD Curses_wattroff(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int ret = wattroff(self ,i1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wattrset(self, Int i1) */

METHOD Curses_wattrset(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int ret = wattrset(self ,i1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wbkgd(self, Int i1) */

METHOD Curses_wbkgd(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int ret = wbkgd(self ,i1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void Curses.wbkgdset(self, Int i1) */

METHOD Curses_wbkgdset(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    wbkgdset(self ,i1 );

    KNH_RETURN_void(ctx, sfp);
}

/* Int Curses.wborder(self, Int i1, Int i2, Int i3, Int i4, Int i5, Int i6, Int i7, Int i8) */

METHOD Curses_wborder(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int i3 = p_int(sfp[3]);
    int i4 = p_int(sfp[4]);
    int i5 = p_int(sfp[5]);
    int i6 = p_int(sfp[6]);
    int i7 = p_int(sfp[7]);
    int i8 = p_int(sfp[8]);
    int ret = wborder(self ,i1 ,i2 ,i3 ,i4 ,i5 ,i6 ,i7 ,i8 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wclear(self) */

METHOD Curses_wclear(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = wclear(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wclrtobot(self) */

METHOD Curses_wclrtobot(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = wclrtobot(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wclrtoeol(self) */

METHOD Curses_wclrtoeol(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = wclrtoeol(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void Curses.wcursyncup(self) */

METHOD Curses_wcursyncup(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    wcursyncup(self );

    KNH_RETURN_void(ctx, sfp);
}

/* Int Curses.wdelch(self) */

METHOD Curses_wdelch(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = wdelch(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wdeleteln(self) */

METHOD Curses_wdeleteln(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = wdeleteln(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wechochar(self, Int i1) */

METHOD Curses_wechochar(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int ret = wechochar(self ,i1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.werase(self) */

METHOD Curses_werase(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = werase(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wgetch(self) */

METHOD Curses_wgetch(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = wgetch(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wgetnstr(self, String s1, Int i2) */

METHOD Curses_wgetnstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    char *s1 = p_char(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = wgetnstr(self ,s1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wgetstr(self, String s1) */

METHOD Curses_wgetstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    char *s1 = p_char(sfp[1]);
    int ret = wgetstr(self ,s1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.whline(self, Int i1, Int i2) */

METHOD Curses_whline(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = whline(self ,i1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.winch(self) */

METHOD Curses_winch(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = winch(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.winnstr(self, String s1, Int i2) */

METHOD Curses_winnstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    char *s1 = p_char(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = winnstr(self ,s1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.winsch(self, Int i1) */

METHOD Curses_winsch(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int ret = winsch(self ,i1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.winsdelln(self, Int i1) */

METHOD Curses_winsdelln(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int ret = winsdelln(self ,i1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.winsertln(self) */

METHOD Curses_winsertln(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = winsertln(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.winsnstr(self, String s1, Int i2) */

METHOD Curses_winsnstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    char *s1 = p_char(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = winsnstr(self ,s1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.winsstr(self, String s1) */

METHOD Curses_winsstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    char *s1 = p_char(sfp[1]);
    int ret = winsstr(self ,s1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.winstr(self, String s1) */

METHOD Curses_winstr(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    char *s1 = p_char(sfp[1]);
    int ret = winstr(self ,s1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wmove(self, Int i1, Int i2) */

METHOD Curses_wmove(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = wmove(self ,i1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wnoutrefresh(self) */

METHOD Curses_wnoutrefresh(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = wnoutrefresh(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wredrawln(self, Int i1, Int i2) */

METHOD Curses_wredrawln(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = wredrawln(self ,i1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wrefresh(self) */

METHOD Curses_wrefresh(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = wrefresh(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wresize(Int i1, Int i2) */

METHOD Curses_wresize(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
    int ret = wresize(self, i1, i2);

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wscrl(self, Int i1) */

METHOD Curses_wscrl(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int ret = wscrl(self ,i1 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wsetscrreg(self, Int i1, Int i2) */

METHOD Curses_wsetscrreg(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = wsetscrreg(self ,i1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wstandout(self) */

METHOD Curses_wstandout(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = wstandout(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wstandend(self) */

METHOD Curses_wstandend(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = wstandend(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* void Curses.wsyncdown(self) */

METHOD Curses_wsyncdown(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    wsyncdown(self );

    KNH_RETURN_void(ctx, sfp);
}

/* void Curses.wsyncup(self) */

METHOD Curses_wsyncup(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    wsyncup(self );

    KNH_RETURN_void(ctx, sfp);
}

/* void Curses.wtimeout(self, Int i1) */

METHOD Curses_wtimeout(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    wtimeout(self ,i1 );

    KNH_RETURN_void(ctx, sfp);
}

/* Int Curses.wtouchln(self, Int i1, Int i2, Int i3) */

METHOD Curses_wtouchln(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int i3 = p_int(sfp[3]);
    int ret = wtouchln(self ,i1 ,i2 ,i3 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wvline(self, Int i1, Int i2) */

METHOD Curses_wvline(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = wvline(self ,i1 ,i2 );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.getAttrs(self) */

METHOD Curses_getAttrs(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = getattrs(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}


/* Int Curses.getCurx(self) */

METHOD Curses_getCurx(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = getcurx(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.getCury(self) */

METHOD Curses_getCury(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = getcury(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.getBegx(self) */

METHOD Curses_getBegx(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = getbegx(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.getBegy(self) */

METHOD Curses_getBegy(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = getbegy(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.getBkgd(self) */

METHOD Curses_getBkgd(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = getbkgd(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.getMaxx(self) */

METHOD Curses_getMaxx(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = getmaxx(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.getMaxy(self) */

METHOD Curses_getMaxy(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = getmaxy(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.getParx(self) */

METHOD Curses_getParx(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = getparx(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.getPary(self) */

METHOD Curses_getPary(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = getpary(self );

    KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int Curses.wgetparent(self) */

METHOD Curses_wgetparent(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    WINDOW *ret = wgetparent(self );

    KNH_RETURN(ctx, sfp, ret);
}

/* Boolean Curses.isCleared(self) */

METHOD Curses_isCleared(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = is_cleared(self );

    KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean Curses.isIdcok(self) */

METHOD Curses_isIdcok(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = is_idcok(self );

    KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean Curses.isIdlok(self) */

METHOD Curses_isIdlok(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = is_idlok(self );

    KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean Curses.isImmedok(self) */

METHOD Curses_isImmedok(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = is_immedok(self );

    KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean Curses.isKeypad(self) */

METHOD Curses_isKeypad(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = is_keypad(self );

    KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean Curses.isLeaveok(self) */

METHOD Curses_isLeaveok(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = is_leaveok(self );

    KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean Curses.isNodelay(self) */

METHOD Curses_isNodelay(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = is_nodelay(self );

    KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean Curses.isNotimeout(self) */

METHOD Curses_isNotimeout(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = is_notimeout(self );

    KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean Curses.isScrollok(self) */

METHOD Curses_isScrollok(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = is_scrollok(self );

    KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean Curses.isSyncok(self) */

METHOD Curses_isSyncok(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int ret = is_syncok(self );

    KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean Curses.wenclose(self, Int i1, Int i2) */

METHOD Curses_wenclose(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *self =(WINDOW*)((sfp[0].glue)->ptr);
    int i1 = p_int(sfp[1]);
    int i2 = p_int(sfp[2]);
    int ret = wenclose(self ,i1 ,i2 );

    KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Curses Curses.newpad(Int i0, Int i1) */

METHOD Curses_newpad(Ctx *ctx, knh_sfp_t* sfp)
{
	WINDOW *win;
	knh_Glue_t *glue = sfp[0].glue;
    int i0 = p_int(sfp[1]);
    int i1 = p_int(sfp[2]);
    initscr();
    noecho();
    cbreak();
    win = newpad(i0 ,i1 );
	glue->ptr = (void*)win;
    KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* Curses Curses_newwin(Int i0, Int i1, Int i2, Int i3) */

METHOD Curses_newwin(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *win;
    knh_Glue_t *glue = sfp[0].glue;
	int i0 = p_int(sfp[1]);
    int i1 = p_int(sfp[2]);
    int i2 = p_int(sfp[3]);
    int i3 = p_int(sfp[4]);
    initscr();
    noecho();
    cbreak();
    win = newwin(i0 ,i1 ,i2 ,i3 );
    glue->ptr = (void*)win;
    KNH_RETURN(ctx, sfp, sfp[0].o);
}


/* Curses_new(Int i1, Int i2, Int i3, Int i4) */
METHOD Curses_new(Ctx *ctx, knh_sfp_t* sfp)
{
    WINDOW *win;
    knh_Glue_t *glue = sfp[0].glue;
    initscr();
    noecho();
    cbreak();
    win = newwin(p_int(sfp[1]), p_int(sfp[2]),
            p_int(sfp[3]), p_int(sfp[4]));
    glue->ptr = (void*)win;
    KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* Curses_getLINES() */
METHOD Curses_getLINES(Ctx *ctx, knh_sfp_t* sfp)
{
	initscr();
	endwin();
    KNH_RETURN_Int(ctx, sfp, LINES);
}

/* Curses_getCOLS() */
METHOD Curses_getCOLS(Ctx *ctx, knh_sfp_t* sfp)
{
	initscr();
	endwin();
    KNH_RETURN_Int(ctx, sfp, COLS);
}

/* ======================================================================== */
/* [ConstData] */

static
knh_IntConstData_t IntConstData[] = {
	{"Curses.KEY_BS", KEY_BACKSPACE},
	{"Curses.KEY_UP", KEY_UP},
	{"Curses.KEY_DOWN", KEY_DOWN},
	{"Curses.KEY_LEFT", KEY_LEFT},
	{"Curses.KEY_RIGHT", KEY_RIGHT},
	{"Curses.KEY_HOME", KEY_HOME},
	{"Curses.KEY_RIGHT", KEY_RIGHT},
	{"Curses.KEY_ENTER", 10},
	{NULL}  // end of const data
};

/* ------------------------------------------------------------------------ */

KNH_EXPORTS(int) init(Ctx *ctx)
{
	KNH_NOTICE(ctx, "loading curses..");
	konoha_loadIntConstData(ctx, IntConstData);

	return 1;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

