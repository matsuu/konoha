#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
# shinpei@ynu(c)2008
# Autoconf for konoha scripting language

AC_PREREQ(2.61)
AC_INIT([konoha], [0.1.1], [konoha-bugs@sourceforge.jp])

# initiate automake with program name, version, -wall option

AM_INIT_AUTOMAKE([konoha], [0.1.1], -Wall)

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
#AC_CHECK_LIB([dl], [dlopen])

# FIXME: Replace `main' with a function in `-liconv':
#AC_CHECK_LIB([iconv], [iconv_open])

# FIXME: Replace `main' with a function in `-lkonoha':
#AC_CHECK_LIB([konoha], [main])
# FIXME: Replace `main' with a function in `-lreadline':
#AC_CHECK_LIB([readline], [main])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([float.h langinfo.h localcharset.h limits.h locale.h stdlib.h string.h sys/time.h unistd.h iconv.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([isascii memset realpath regcomp])

AC_CONFIG_FILES([Makefile
		 build/Makefile
		 package/Makefile
		 package/math/Makefile])

# debug mode check
# if its set, --enable-debug=yes, then compiled with
# -DKONOHA_DEBUG

AC_ARG_ENABLE(debug,
[  --enable-debug            trun on debugging [default no]])
if test "$enable_debug" = "yes"; then
  CFLAGS="-DKNH_DEBUG $CFLAGS"
fi

# debug mode check
# if its set --enable-fastmode=yes, then compiled with
# -DKONOHA_FASTMODE

AC_ARG_ENABLE(fastmode,
[  --enable-fastmode            trun on fastmode [default no]])
if test "$enable_fastmode" = "yes"; then
  CFLAGS="-DKONOHA_FASTMODE $CFLAGS"
fi


# define macros for each operating system.
# available for linux, cygwin, mingw, darwin.(present)
case "${host_os}" in 
       *linux*) linux=true
	ldl=true;;
       *cygwin*) cygwin=true;;
       *mingw*) mingw=true;;
       *darwin*) macosx=true;;
       *)
	AC_MSG_RESULT([no (${host_os})])
	AC_MSG_ERROR([Unsupported host os, Sorry. Please consider doing a port.])
esac


AM_CONDITIONAL([LINUX], [test x$linux = xtrue])
AM_CONDITIONAL([CYGWIN], [test x$cygwin = xtrue])
AM_CONDITIONAL([MINGW], [test x$mingw = xtrue])
AM_CONDITIONAL([MACOSX], [test x$macosx = xtrue])
AM_CONDITIONAL([LDL], [test x$ldl = xtrue])

# define macros for konoha
AC_DEFINE_UNQUOTED([ACCONFIG_KONOHA_OS], [${host_os}], Defining KONOHA_OS_MACROS)

AC_OUTPUT
