AC_PREREQ([2.69])
AC_INIT([vinnie], [0.1.1-alpha], [https://github.com/clpo13/vinnie/issues], [vinnie], [https://github.com/clpo13/vinnie])
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([1.11 foreign dist-xz])
AM_SILENT_RULES([yes])

# Checks for programs.
PKG_PROG_PKG_CONFIG
AC_PROG_CPP
AC_PROG_CC_C99
AC_ENABLE_SHARED
AC_DISABLE_STATIC
LT_INIT([win32-dll])

# Checks for libraries.
PKG_CHECK_MODULES([CHECK], [check], [have_libcheck=yes], [have_libcheck=no])
AS_IF([test "$have_libcheck" = "no"], [
    AC_MSG_WARN([Check not found. Unit tests will not be built.])
])
AM_CONDITIONAL([HAVE_CHECK], [test "$have_libcheck" = "yes"])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([strchr])

# Set up Makefiles.
AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT
