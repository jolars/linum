LIBS=lib/libresistance.so lib/libpower.so lib/libcomponent.so
CFLAGS=-Wall -std=c99
CC=gcc

.PHONY: all
all: lib electrotest

.PHONY: lib
lib: $(LIBS)

electrotest:
	# temp: använder testpower.c som test innan vi skrivit electrotest
	$(CC) $(CFLAGS) -o $@ electrotest.c -L $(LIBS) -lm -Wl,-rpath,lib/

lib/%.so: %.o
	mkdir -p lib/
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -fPIC $<

.PHONY: install
install:
	# "och länkar så att programmet använder de publika biblioteken"
	# verkar inte behövas på mitt system, konstigt
	sudo cp $(LIBS) /usr/lib/
	sudo cp electrotest /usr/bin/

.PHONY: uninstall
uninstall:
	sudo rm $(addprefix /usr/,$(LIBS))
	sudo rm /usr/bin/electrotest

#.PRECIOUS: %.o
