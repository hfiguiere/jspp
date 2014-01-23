
AM_CPPFLAGS = @MOZJS_CFLAGS@
AM_LDFLAGS = @MOZJS_LIBS@

check_PROGRAMS = js++-test


js___test_SOURCES = test.cpp
js___test_LDADD = libjs++.la

lib_LTLIBRARIES = libjs++.la

libjs___la_SOURCES = \
	binder.cpp binder.hpp \
	context.cpp context.hpp \
	runtime.cpp runtime.hpp \
	$(NULL)
