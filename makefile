LIBS=libpower.so # lägg till era bibliotek
CFLAGS=-Wall -std=c99
CC=gcc
 
.PHONY: all
all: lib electrotest

.PHONY: lib
lib: $(LIBS)

electrotest:
	# temp: använder testpower.c som test innan vi skrivit electrotest
	$(CC) $(CFLAGS) testpower.c -o $@ -Llib/ $(basename $(subst lib,-l,$(LIBS))) -lm -Wl,-rpath,lib/

%.so: %.o
	mkdir -p lib/
	$(CC) $(CFLAGS) -shared -fPIC -o lib/$@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -fPIC $<	

.PHONY: install
install:
	# "och länkar så att programmet använder de publika biblioteken"
	# verkar inte behövas på mitt system, konstigt
	sudo cp $(addprefix lib/,$(LIBS)) /usr/lib
	sudo cp electrotest /usr/bin/

.PHONY: uninstall
uninstall:
	sudo rm $(addprefix /usr/lib/,$(LIBS))
	sudo rm /usr/bin/electrotest
