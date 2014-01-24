
AM_CPPFLAGS = @MOZJS_CFLAGS@
AM_LDFLAGS = @MOZJS_LIBS@

check_PROGRAMS = js++-test-rt

TESTS = js++-test-rt

js___test_rt_SOURCES = test-rt.cpp
js___test_rt_LDADD = libjs++.la

lib_LTLIBRARIES = libjs++.la

libjs___la_SOURCES = \
	binder.cpp binder.hpp \
	context.cpp context.hpp \
	runtime.cpp runtime.hpp \
	$(NULL)
