LIBS=lib/libresistance.so lib/libpower.so lib/libcomponent.so
CFLAGS=-Wall -std=c99
CC=gcc

.PHONY: all
all: lib electrotest

.PHONY: lib
lib: $(LIBS)

electrotest: electrotest.c
	$(CC) $(CFLAGS) -o $@ electrotest.c -Llib/ $(basename $(subst lib/lib,-l,$(LIBS))) -lm -Wl,-rpath,lib/

lib/%.so: %.o
	mkdir -p lib/
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -fPIC $<

.PHONY: clean
clean:
	rm -rf lib
	rm electrotest

.PHONY: install
install:
	# "och länkar så att programmet använder de publika biblioteken"
	# verkar inte behövas på mitt system, konstigt
	cp $(LIBS) /usr/lib
	cp electrotest /usr/bin/

.PHONY: uninstall
uninstall:
	rm $(addprefix /usr/,$(LIBS))
	rm /usr/bin/electrotest

#.PRECIOUS: %.o
