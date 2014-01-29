
AM_CPPFLAGS = @MOZJS_CFLAGS@
AM_LDFLAGS = @MOZJS_LIBS@

check_PROGRAMS = js++-test-rt js++-test-call

TESTS = js++-test-rt js++-test-call

js___test_rt_SOURCES = test-rt.cpp test-utils.cpp
js___test_rt_LDADD = libjs++.la

js___test_call_SOURCES = test-call.cpp test-utils.cpp
js___test_call_LDADD = libjs++.la

lib_LTLIBRARIES = libjs++.la

libjs___la_SOURCES = \
	binder.cpp binder.hpp \
	context.cpp context.hpp \
	runtime.cpp runtime.hpp \
	$(NULL)
