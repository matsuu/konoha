#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
# shinpei@ynu(c)2008
# Autoconf for konoha scripting language

# required Autoconf version
AC_PREREQ(2.61)
#initiate Autoconf

AC_INIT([konoha], [0.5rc2], [konoha-bugs@list.sourceforge.jp])

# initiate automake with program name, version, -wall option

AM_INIT_AUTOMAKE([konoha], [0.5rc2], -Wall)

AC_CONFIG_SRCDIR([build/Makefile.in])
AC_CONFIG_HEADER([config.h])
# Checks for programs.

AC_PROG_CC
AC_PROG_INSTALL

# configure options for shared library option
# only compile shared library, not static.

AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

# Checks for libraries.
# FIXME: Replace `main' with a function in `-ldl':

########################################################################
## OS
case "${host_os}" in 
*cygwin*) ;;
*darwin*) ;;
*) AC_CHECK_LIB([dl], [dlopen]);;
esac

case "${host_os}" in 
*cygwin*) ;;
*darwin*) ;;
*) AC_CHECK_LIB([m], [sin]);;
esac

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([float.h langinfo.h localcharset.h limits.h locale.h stdlib.h string.h sys/time.h unistd.h iconv.h readline/readline.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([isascii memset realpath])

# Options ###### ############################################################
# Kimio Kuramitsu

AC_ARG_ENABLE(rcgc,
AC_HELP_STRING([--enable-rcgc], [referencing counting mode [[default=no]]]),
[case $enableval in
yes|no) ;;
*) AC_MSG_ERROR([bad value $withval for --enable-rcgc, need yes/no]) ;;
esac],
[enable_mono=no])

if test $enable_rcgc = yes; then
  AC_DEFINE_UNQUOTED([KNH_USING_RCGC], [1], Enable referencing counting mode)
fi

AC_ARG_ENABLE(debug,
AC_HELP_STRING([--enable-debug], [debug mode [[default=no]]]),
[case $enableval in
yes|1|2|no) ;;
*) AC_MSG_ERROR([bad value $withval for --enable-debug, need yes/no/2]) ;;
esac],
[enable_debug=no])

if test $enable_debug = yes; then
  AC_DEFINE_UNQUOTED([KNH_DBGMODE], [1], Enable debug mode)
fi
if test $enable_debug = 1; then
  AC_DEFINE_UNQUOTED([KNH_DBGMODE], [1], Enable debug mode)
fi
if test $enable_debug = 2; then
  AC_DEFINE_UNQUOTED([KNH_DBGMODE2], [1], Enable debug mode level2)
fi

AC_ARG_ENABLE(int32,
AC_HELP_STRING([--enable-int32], [int32 mode [[default=no]]]),
[case $enableval in
yes|no) ;;
*) AC_MSG_ERROR([bad value $withval for --enable-int32, need yes/no]) ;;
esac],
[enable_int32=no])

if test $enable_int32 = yes; then
  AC_DEFINE_UNQUOTED([KNH_USING_INT32], [1], Enable int32)
fi

with_regex=no
AC_CHECK_HEADER(regex.h, with_regex=yes)

if test $with_regex = 2; then
  AC_DEFINE_UNQUOTED([KNH_USING_REGEX], [1], Using regex)
fi

# ADDED for mtune ############################################################
# Kimio Kuramitsu

AC_ARG_ENABLE(fastmode,
AC_HELP_STRING([--enable-fastmode],
               [if you like fast-things [[default=no]]]),
[case $enableval in
yes|core2|no) ;;
*) AC_MSG_ERROR([bad value $withval for --enable-fastmode, need yes/core2/no]) ;;
esac],
[with_fastmode=no])

use_fastmode=$with_fastmode
with_mtune=no
if test $use_fastmode = yes; then
  with_mtune=$host_cpu
  CFLAGS="-mtune=$with_mtune -fomit-frame-pointer $CFLAGS"
fi
if test $use_fastmode = core2; then
  with_mtune=core2
  CFLAGS="-m64 -march=core2 -mtune=core2 -fomit-frame-pointer $CFLAGS"
fi

if test $with_mtune = no; then
  WITHOUT_MTUNE=0
else
  AC_DEFINE_UNQUOTED([KONOHA_CC_CPU], ["{$with_mtune}"], mtune option)
fi

# ADDED for iconv ############################################################
# Kimio Kuramitsu

AC_ARG_WITH(iconv,
AC_HELP_STRING([--with-iconv],
               [iconv support [[default=detect]]]),
[case $withval in
yes|no|detect) ;;
*) AC_MSG_ERROR([bad value $withval for --with-readline, need yes/no/detect]) ;;
esac],
[with_iconv=detect])

use_iconv=$with_iconv
if test $with_iconv = detect; then
  use_iconv=no
  AC_CHECK_LIB(iconv, iconv_open, use_iconv=yes)
  AC_CHECK_LIB(c, iconv_open, with_iconv=yes)
  AC_MSG_CHECKING(iconv detected)
  AC_MSG_RESULT($use_iconv)
fi
if test $with_iconv = yes; then
  AC_DEFINE_UNQUOTED([KNH_USING_ICONV], [1], Using iconv)
  AC_SUBST(WITH_ICONV_01, 1)
else
  WITH_ICONV_01=0
fi
if test $use_iconv = yes; then
  AC_SUBST(LIBICONV, -liconv)
  LIBS="$LIBS -liconv"
fi

# ADDED for readline #########################################################
# Kimio Kuramitsu

AC_ARG_WITH(readline,
AC_HELP_STRING([--with-readline],
               [readline support [[default=detect]]]),
[case $withval in
yes|no|detect) ;;
*) AC_MSG_ERROR([bad value $withval for --with-readline, need yes/no/detect]) ;;
esac],
[with_readline=detect])

with_libcurses=no
LIBCURSES=
if test $with_readline != no; then
  AC_CHECK_LIB(ncurses, tputs, [with_libcurses=yes],
    [AC_CHECK_LIB(curses, tputs, [with_libcurses=yes])])
fi
#AC_SUBST(LIBCURSES)

case "${host_os}" in 
*cygwin*) use_readline=no;;
*) use_readline=$with_readline
esac

if test $use_readline = detect; then
  use_readline=no
  AC_CHECK_LIB(readline, readline,
    [AC_CHECK_HEADER(readline/readline.h,
      [AC_CHECK_HEADER(readline/history.h, use_readline=yes)])],
    , $LIBCURSES)
  AC_MSG_CHECKING(readline detected)
  AC_MSG_RESULT($use_readline)
fi
if test $use_readline = yes; then
  AC_SUBST(WITH_READLINE_01, 1)
  AC_SUBST(LIBREADLINE, -lreadline)
  AC_DEFINE_UNQUOTED([KNH_USING_READLINE], [1], Using readline)
  if test $with_libcurses = yes; then
    LIBS="$LIBS -lncurses"
  fi
  LIBS="$LIBS -lreadline"
else
  WITH_READLINE_01=0
fi

# ADDED for socket ###########################################################
# Kimio Kuramitsu

AC_ARG_WITH(socket,
AC_HELP_STRING([--with-socket],
               [socket support [[default=detect]]]),
[case $withval in
yes|no|detect) ;;
*) AC_MSG_ERROR([bad value $withval for --with-socket, need yes/no/detect]) ;;
esac],
[with_socket=detect])

use_socket=$with_socket
if test $with_socket = detect; then
  use_socket=no
  AC_CHECK_LIB(socket, socket, use_socket=yes)
  AC_CHECK_LIB(c, socket, with_socket=yes)
  AC_MSG_CHECKING(socket detected)
  AC_MSG_RESULT($use_socket)
fi
if test $with_socket = yes; then
  AC_DEFINE_UNQUOTED([KNH_USING_SOCKET], [1], Using socket)
  AC_SUBST(WITH_SOCKET_01, 1)
else
  WITH_SOCKET_01=0
fi
if test $use_socket = yes; then
  AC_SUBST(LIBSOCKET, -lsocket)
  LIBS="$LIBS -lsocket"
fi

# ADDED for sqlite3 ###########################################################
# Kimio Kuramitsu

AC_ARG_WITH(sqlite3,
AC_HELP_STRING([--with-sqlite3],
               [sqlite3 support [[default=detect]]]),
[case $withval in
yes|no|detect) ;;
*) AC_MSG_ERROR([bad value $withval for --with-sqlite3, need yes/no/detect]) ;;
esac],
[with_sqlite3=detect])

use_sqlite3=$with_sqlite3
if test $with_sqlite3 = detect; then
  use_sqlite3=no
  AC_CHECK_LIB(sqlite3, sqlite3_open, use_sqlite3=yes)
  AC_MSG_CHECKING(sqlite3 detected)
  AC_MSG_RESULT($use_sqlite3)
fi
if test $use_sqlite3 = yes; then
  AC_DEFINE_UNQUOTED([KNH_USING_SQLITE3], [1], Using sqlite3)
  AC_SUBST(LIBSQLITE3, -lsqlite3)
  LIBS="$LIBS -lsqlite3"
fi

# ADDED for thread ###########################################################
# Kimio Kuramitsu

AC_ARG_ENABLE(thread,
AC_HELP_STRING([--with-thread],
               [enable multithreading..  [[default=detect]]]),
[case $withval in
yes|no|detect) ;;
*) AC_MSG_ERROR([bad value $withval for --with-thread, need yes/no/detect]) ;;
esac],
[with_thread=detect])

use_thread=$with_thread
if test $with_thread = detect; then
  use_thread=no
  AC_CHECK_LIB(pthread, pthread_create, use_thread=yes)
  AC_MSG_CHECKING(pthread detected)
  AC_MSG_RESULT($use_thread)
  if test $use_thread = yes; then
    AC_DEFINE_UNQUOTED([KNH_USING_PTHREAD], [1], Using pthread detected)
  fi
fi
if test $use_thread = yes; then
  AC_DEFINE_UNQUOTED([KNH_USING_THREAD], [1], Using thread)
  AC_SUBST(WITH_THREAD_01, 1)
  AC_SUBST(LIBTHREAD, -lpthread)
  LIBS="$LIBS -lpthread"
else
  WITH_THREAD_01=0
fi

#############################################################################

AC_CONFIG_FILES([Makefile
		 build/Makefile])

# define macros for each operating system.
# available for linux, cygwin, mingw, darwin.(present)
#case "${host_os}" in 
#       *linux*) linux=true
#	ldl=true;;
#       *cygwin*) cygwin=true;;
#       *mingw*) mingw=true;;
#       *darwin*) 
#           macosx=true;;
#       *)
#	AC_MSG_RESULT([no (${host_os})])
#	AC_MSG_ERROR([Unsupported host os, Sorry. Please consider doing a port.])
#      *) unknown=true;;
#esac

#AM_CONDITIONAL([LINUX], [test x$linux = xtrue])
#AM_CONDITIONAL([CYGWIN], [test x$cygwin = xtrue])
#AM_CONDITIONAL([MINGW], [test x$mingw = xtrue])
#AM_CONDITIONAL([MACOSX], [test x$macosx = xtrue])
#AM_CONDITIONAL([UNKNOWN], [test x$unknown = xtrue])
#AM_CONDITIONAL([LDL], [test x$ldl = xtrue])

# define macros for konoha
AC_DEFINE_UNQUOTED([ACCONFIG_KONOHA_OS], [${host_os}], Defining KONOHA_OS_MACROS)

AC_MSG_RESULT([this is ${prefix}])
if  test  "${prefix}" != "NONE" ; then
  AC_DEFINE_UNQUOTED([KNH_PREFIX], ["${prefix}"], Defineing konoha prefix install folder)
else
  AC_DEFINE_UNQUOTED([KNH_PREFIX], "$ac_default_prefix", Difining konoha library prefix with default value)
fi

AC_DEFINE_UNQUOTED([KONOHA_CONFIG_OS], ["${host_os}"], Konoha os type)

AC_OUTPUT
