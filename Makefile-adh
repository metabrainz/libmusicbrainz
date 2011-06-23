VERSION=1.0-alpha1
BASEDIR=/usr

all: src

src: .phony
	$(MAKE) -C src

clean: .phony
	rm -rf libmusicbrainz4
	$(MAKE) -C src clean

dist: clean
	mkdir libmusicbrainz4
	cp -r COPYING Makefile src include libmusicbrainz4 && tar cf - --exclude "\.svn" libmusicbrainz4 | gzip -9 > libmusicbrainz4-$(VERSION).tar.gz

install: all
	mkdir -p $(BASEDIR)/include
	cp -ar include/* $(BASEDIR)/include
	cp src/libmusicbrainz4.so $(BASEDIR)/lib
	
.phony:
