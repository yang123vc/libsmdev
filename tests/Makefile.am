AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBSMDEV_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	smdev_test_error \
	smdev_test_handle \
	smdev_test_notify \
	smdev_test_support

smdev_test_error_SOURCES = \
	smdev_test_error.c \
	smdev_test_libsmdev.h \
	smdev_test_macros.h \
	smdev_test_unused.h

smdev_test_error_LDADD = \
	../libsmdev/libsmdev.la

smdev_test_handle_SOURCES = \
	smdev_test_handle.c \
	smdev_test_libcerror.h \
	smdev_test_libclocale.h \
	smdev_test_libcsystem.h \
	smdev_test_libsmdev.h \
	smdev_test_libuna.h \
	smdev_test_memory.c smdev_test_memory.h \
	smdev_test_unused.h

smdev_test_handle_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libsmdev/libsmdev.la \
	@LIBCERROR_LIBADD@

smdev_test_notify_SOURCES = \
	smdev_test_libsmdev.h \
	smdev_test_macros.h \
	smdev_test_notify.c \
	smdev_test_unused.h

smdev_test_notify_LDADD = \
	../libsmdev/libsmdev.la

smdev_test_support_SOURCES = \
	smdev_test_libcerror.h \
	smdev_test_libsmdev.h \
	smdev_test_macros.h \
	smdev_test_support.c \
	smdev_test_unused.h

smdev_test_support_LDADD = \
	../libsmdev/libsmdev.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

