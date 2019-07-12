AC_PREREQ([2.69])
AC_INIT([vinnie], [0.1.1-alpha], [], [], [https://github.com/clpo13/vinnie])
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
PKG_PROG_PKG_CONFIG
AC_PROG_CPP
AC_PROG_CC
AC_ENABLE_SHARED
AC_DISABLE_STATIC
LT_INIT

# Checks for libraries.
PKG_CHECK_MODULES([CHECK], [check], [have_libcheck=yes], [have_libcheck=no])
AM_CONDITIONAL([CHECK], [test "$have_libcheck" = "yes"])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([strchr])

AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT
