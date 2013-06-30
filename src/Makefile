include ../package.mk
include ../config.mk

CFLAGS := -Wall -Wextra -Werror -g -std=c99 $(CFLAGS)
CPPFLAGS := -I../include $(CPPFLAGS)
LIBTOOL_VERSION := $(LIBTOOL_CURRENT):$(LIBTOOL_REVISION):$(LIBTOOL_AGE)

OBJS := $(patsubst %.c,%.lo,$(wildcard *.c))

all: $(LIBRARY_NAME)

$(LIBRARY_NAME): $(OBJS)
	$(LIBTOOL) --mode=link $(CC) $(LDFLAGS) -rpath $(LIBDIR) -version-info $(LIBTOOL_VERSION) -release $(PACKAGE_RELEASE) -o $@ $^

%.lo: %.c
	$(LIBTOOL) --mode=compile $(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

install: $(LIBRARY_NAME)
	$(LIBTOOL) --mode=install $(INSTALL) $< $(LIBDIR)

clean:
	rm -rf *.o *.lo .libs $(LIBRARY_NAME)
