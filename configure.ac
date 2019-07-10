AC_PREREQ([2.69])
AC_INIT([vinnie], [0.1.1-alpha], [], [], [https://github.com/clpo13/vinnie])
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign])
PKG_PROG_PKG_CONFIG

# Checks for programs.
AC_PROG_CPP
AC_PROG_CC

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
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT
