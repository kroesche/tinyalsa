DESTDIR ?=
PREFIX ?= /usr/local
LIBDIR ?= $(PREFIX)/lib
BINDIR ?= $(PREFIX)/bin
ifdef DEB_HOST_MULTIARCH
LIBDIR := $(LIBDIR)/$(DEB_HOST_MULTIARCH)
endif

CROSS_COMPILE =
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)gcc

WARNINGS = -Wall -Wextra -Werror -Wfatal-errors
INCLUDE_DIRS = -I ../include
override CFLAGS := $(WARNINGS) $(INCLUDE_DIRS) -fPIC $(CFLAGS)

VPATH = ../include/tinyalsa
OBJECTS = limits.o mixer.o pcm.o pcm-config.o pcm-format.o hw-params.o

.PHONY: all
all: libtinyalsa.a libtinyalsa.so

hw-params.o: hw-params.c hw-params.h

pcm.o: pcm.c pcm.h hw-params.h

pcm-config.o: pcm-config.c pcm-config.h pcm-format.h

pcm-format.o: pcm-format.c pcm-format.h

limits.o: limits.c limits.h

mixer.o: mixer.c mixer.h

libtinyalsa.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

libtinyalsa.so: libtinyalsa.so.1
	ln -sf $< $@

libtinyalsa.so.1: libtinyalsa.so.1.1.1
	ln -sf $< $@

libtinyalsa.so.1.1.1: $(OBJECTS)
	$(LD) $(LDFLAGS) -shared -Wl,-soname,libtinyalsa.so.1 $^ -o $@

.PHONY: clean
clean:
	rm -f libtinyalsa.a
	rm -f libtinyalsa.so
	rm -f libtinyalsa.so.1
	rm -f libtinyalsa.so.1.1.1
	rm -f $(OBJECTS)

.PHONY: install
install: libtinyalsa.a libtinyalsa.so.1
	install -d $(DESTDIR)$(LIBDIR)/
	install libtinyalsa.a $(DESTDIR)$(LIBDIR)/
	install libtinyalsa.so.1.1.1 $(DESTDIR)$(LIBDIR)/
	ln -sf libtinyalsa.so.1.1.1 $(DESTDIR)$(LIBDIR)/libtinyalsa.so.1
	ln -sf libtinyalsa.so.1 $(DESTDIR)$(LIBDIR)/libtinyalsa.so

