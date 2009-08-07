/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2009-      Konoha Software Foundation
 * All rights reserved.
 *
 * You may choose one of the following two licenses when you use konoha.
 * See www.konohaware.org/license.html for further information.
 *
 * (1) GNU General Public License 2.0      (with    KONOHA_UNDER_GPL2)
 * (2) Konoha Software Foundation License 1.0
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/* ************************************************************************ */

#include<konoha.h>
#include <konoha/gen/konoha_proto_.h>

#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif


/* ======================================================================== */
/* ConstData */

static
knh_IntConstData_t IntConstData[] = {
    {"System.SIG_HUP", SIGHUP},   // hang up (1)
    {"System.SIG_INT", SIGINT},   // interrupt (2)
    {"System.SIG_QUIT", SIGQUIT}, // quit (3)
    {"System.SIG_ABRT", SIGABRT}, // abort (9)
    {"System.SIG_KILL", SIGKILL}, // kill 9
    {"System.SIG_ALRM", SIGALRM}, // alarm clock (14)
    {"System.SIG_TERM", SIGTERM}, // software termination signal 15
    {"System.SIG_BUS",  SIGBUS},
    {"System.SIG_SEGV", SIGSEGV},
    {NULL}  // end of const data
};

static
knh_FloatConstData_t FloatConstData[] = {
    {NULL}  // end of const data
};

static
knh_StringConstData_t StringConstData[] = {
    {NULL}  // end of const data
};

/* ======================================================================== */
/* [API] */

/* ------------------------------------------------------------------------ */
// String! System.getHostName();

METHOD System_getHostName(Ctx *ctx, knh_sfp_t *sfp)
{
    char buf[256];
    if(gethostname(buf, sizeof(buf)) == -1) {
        KNH_PERRNO(ctx, NULL,"OS!!", "gethostname", 1);
    }
    KNH_RETURN(ctx, sfp, new_String(ctx, B(buf), NULL));
}

/* ------------------------------------------------------------------------ */
// String System.getLogin();

METHOD System_getLogin(Ctx *ctx, knh_sfp_t *sfp)
{
    KNH_RETURN(ctx, sfp, new_String(ctx, B(getlogin()),NULL));
}

/* ------------------------------------------------------------------------ */
// int System.getUid();

METHOD System_getUid(Ctx *ctx, knh_sfp_t *sfp)
{
    KNH_RETURN_Int(ctx, sfp, getuid());
}

/* ------------------------------------------------------------------------ */
// int System.getPid();

METHOD System_getPid(Ctx *ctx, knh_sfp_t *sfp)
{
    KNH_RETURN_Int(ctx, sfp, getpid());
}

/* ------------------------------------------------------------------------ */
// int System.getPPid();

METHOD System_getPPid(Ctx *ctx, knh_sfp_t *sfp)
{
    KNH_RETURN_Int(ctx, sfp, getppid());
}

/* ------------------------------------------------------------------------ */
// void System.kill(int pid, int signal);

METHOD System_kill(Ctx *ctx, knh_sfp_t *sfp)
{
    KNH_SECURE(ctx, sfp);
    if(kill(p_int(sfp[1]), p_int(sfp[2])) == -1) {
        KNH_PERRNO(ctx, NULL,"OS!!", "kill", knh_Context_isStrict(ctx));
    }
    KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
// int System.system(String! cmd);

METHOD System_system(Ctx *ctx, knh_sfp_t *sfp)
{
    //    KNH_SECURE(ctx, sfp);
    int ret = system(p_char(sfp[1]));
    if(ret  == -1) {
        KNH_PERRNO(ctx, NULL,"OS!!", "system", knh_Context_isStrict(ctx));
    }
    KNH_RETURN_Int(ctx, sfp,ret);
}


/* ------------------------------------------------------------------------ */
// void System.sleep(int sec);

METHOD System_sleep(Ctx *ctx, knh_sfp_t *sfp)
{
    int sec = p_int(sfp[1]);
    sleep(sec);
    KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
// void System.setSigSegv(Closure c);

Closure *segvfunc = NULL;
static void knh_sig_segv(int sig)
{
    Ctx *lctx = knh_getCurrentContext();
    knh_sfp_t *lsfp = KNH_LOCAL(lctx);
    knh_Closure_invokesfp(lctx, segvfunc, lsfp, 0);
}

struct sigaction sa_seg;
METHOD System_setSigSegv(Ctx *ctx, knh_sfp_t *sfp)
{
    segvfunc = sfp[1].cc;
    memset(&sa_seg, 0, sizeof(struct sigaction));
    sa_seg.sa_handler = knh_sig_segv;
    sigaction(SIGSEGV, &sa_seg, NULL);
    KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
// void System.setSigBus(Closure c);
Closure *busfunc = NULL;
static void knh_sig_bus(int sig)
{
    Ctx *lctx = knh_getCurrentContext();
    knh_sfp_t *lsfp = KNH_LOCAL(lctx);
    knh_Closure_invokesfp(lctx, busfunc, lsfp, 0);
}

struct sigaction sa_bus;
METHOD System_setSigBus(Ctx *ctx, knh_sfp_t *sfp)
{
    busfunc = sfp[1].cc;
    memset(&sa_bus, 0, sizeof(struct sigaction));
    sa_bus.sa_handler = knh_sig_bus;
    sigaction(SIGBUS, &sa_bus, NULL);
    KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
// void System.setSigKill(Closure c);
Closure *killfunc = NULL;
static void knh_sig_kill(int sig)
{
    Ctx *lctx = knh_getCurrentContext();
    knh_sfp_t *lsfp = KNH_LOCAL(lctx);
    knh_Closure_invokesfp(lctx, killfunc, lsfp, 0);
}

struct sigaction sa_kill;
METHOD System_setSigKill(Ctx *ctx, knh_sfp_t *sfp)
{
    killfunc = sfp[1].cc;
    memset(&sa_kill, 0, sizeof(struct sigaction));
    sa_kill.sa_handler = knh_sig_kill;
    sigaction(SIGKILL, &sa_kill, NULL);
    KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
// void System.setSigInt(Closure c);
Closure *intfunc = NULL;
static void knh_sig_int(int sig)
{
    Ctx *lctx = knh_getCurrentContext();
    knh_sfp_t *lsfp = KNH_LOCAL(lctx);
    knh_Closure_invokesfp(lctx, intfunc, lsfp, 0);
}

struct sigaction sa_int;
METHOD System_setSigInt(Ctx *ctx, knh_sfp_t *sfp)
{
    intfunc = sfp[1].cc;
    memset(&sa_int, 0, sizeof(struct sigaction));
    sa_int.sa_handler = knh_sig_int;
    sigaction(SIGINT, &sa_int, NULL);
    KNH_RETURN_void(ctx, sfp);
}


/* ------------------------------------------------------------------------ */
// void System.raise(int signal);
METHOD System_reboot(Ctx *ctx, knh_sfp_t *sfp)
{
  system("reboot");
}  
/* ------------------------------------------------------------------------ */
// void System.raise(int signal);
METHOD System_raise(Ctx *ctx, knh_sfp_t *sfp)
{
    int sig = p_int(sfp[1]);
    fprintf(stderr,"raise:%d\n",sig);
    raise(sig);
    KNH_RETURN_void(ctx, sfp);
}

/* ======================================================================== */
/* [FILESYSTEM] */

/* ------------------------------------------------------------------------ */
// String! System.getCwd();

METHOD System_getCwd(Ctx *ctx, knh_sfp_t *sfp)
{
    // TODO: when filename is longer than 1024
    // to escape this, if we use getcwd(NULL, 0), system malloc buf for filename.
    char *res = NULL;
    char tmpbuf[FILEPATH_BUFSIZ];
    res = getcwd(tmpbuf, sizeof(tmpbuf));
    if (res == NULL) {
        KNH_PERRNO(ctx, NULL,"OS!!", "getcwd", knh_Context_isStrict(ctx));
    }
    String *s = new_String(ctx, B(tmpbuf), NULL);
    KNH_RETURN(ctx, sfp, s);
}

/* ------------------------------------------------------------------------ */
// void System.chDir(String dirname);

METHOD System_chDir(Ctx *ctx, knh_sfp_t *sfp)
{
    char dirname[FILEPATH_BUFSIZ];
    knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
    knh_bytes_t t = (IS_NULL(sfp[1].s)) ? STEXT(".") : knh_String_tobytes(sfp[1].s);
    knh_cwb_write(ctx, cwb, t);
    knh_cwb_ospath(ctx, cwb);

    //knh_format_ospath(ctx, dirname, sizeof(dirname), t);
    String* str = (String *) sfp[1].s;
    knh_bytes_t bt = {str->str, str->size};
    knh_cwb_write(ctx, cwb, bt);
    snprintf(dirname,sizeof(dirname),knh_cwb_tochar(ctx, cwb));
    if(chdir(dirname) == -1) {
        KNH_PERRNO(ctx, NULL,"OS!!", "chdir", knh_Context_isStrict(ctx));
    }
    KNH_RETURN_void(ctx, sfp);
}

/* ======================================================================== */
/* [PIPE] */

    static
knh_io_t knh_iodrv_open__PIPE(Ctx *ctx, knh_bytes_t file, char *mode, int isThrowable)
{
    char *cmd = (char*)knh_bytes_skipscheme(file).buf;
    FILE *fp = NULL;
    
    KNH_WARNING(ctx, "opening pipe '%s'", cmd);
    //KNH_SECURE(ctx, sfp);
    if(mode != NULL && mode[0] == 'r') {
        fp = popen(cmd, "r");
    }
    else {
        fp = popen(cmd, "w");
    }
    if(fp == NULL) {
        KNH_PERRNO(ctx, NULL,"IO!!", "popen", isThrowable);
        return (knh_io_t)-1;
    }
    return (knh_io_t)fp;
}

/* ------------------------------------------------------------------------ */

    static
void knh_iodrv_init__NOP(Ctx *ctx, Object *stream, char *mode)
{
}

/* ------------------------------------------------------------------------ */

    static
knh_intptr_t knh_iodrv_read__PIPE(Ctx *ctx, knh_io_t fd, char *buf, size_t bufsiz)
{
    FILE *fp = (FILE*)fd;
    size_t ssize = fread(buf, 1, bufsiz, fp);
    return ssize;
}

/* ------------------------------------------------------------------------ */

    static
knh_intptr_t knh_iodrv_write__PIPE(Ctx *ctx, knh_io_t fd, char *buf, size_t bufsiz)
{
    FILE *fp = (FILE*)fd;
    size_t ssize = fwrite(buf, 1, bufsiz, fp);
    fflush(fp);
    return ssize;
}

/* ------------------------------------------------------------------------ */

    static
void knh_iodrv_close__PIPE(Ctx *ctx, knh_io_t fd)
{
    FILE *fp = (FILE*)fd;
    pclose(fp);
}

/* ------------------------------------------------------------------------ */
/* @data */

static knh_iodrv_t IO__PIPE = {
    KNH_DRVAPI_TYPE__IO, "pipe",
    0,
    knh_iodrv_open__PIPE,
    knh_iodrv_init__NOP,
    knh_iodrv_read__PIPE,
    knh_iodrv_write__PIPE,
    knh_iodrv_close__PIPE
};

/* ======================================================================== */

KNHAPI(int) init(Ctx *ctx)
{
    KNH_NOTICE(ctx, "loading posix package ..");
    knh_loadIntConstData(ctx, IntConstData);
    knh_loadFloatConstData(ctx, FloatConstData);
    knh_loadStringConstData(ctx, StringConstData);

    // pipe dirver
    knh_addIODriver(ctx, NULL, &IO__PIPE);
    knh_addIODriver(ctx, "sh", &IO__PIPE);
    knh_addIODriver(ctx, "cmd", &IO__PIPE);
    return 1;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

