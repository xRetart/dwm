include config.mk

SRC_DIR = src
OBJ_DIR = obj
SRC = $(SRC_DIR)/dwm.c $(SRC_DIR)/drw.c $(SRC_DIR)/util.c
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

dwm: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(OBJ): $(SRC_DIR)/config.h config.mk
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir --parents obj
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	$(RM) -r $(OBJ_DIR) dwm

install: dwm
	mkdir --parents $(DESTDIR)$(PREFIX)/bin
	install --mode=755 --strip dwm $(DESTDIR)$(PREFIX)/bin
	mkdir --parents $(DESTDIR)$(MANPREFIX)/man1
	sed s/VERSION/$(VERSION)/g < dwm.1 > $(DESTDIR)$(MANPREFIX)/man1/dwm.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/dwm.1

uninstall:
	$(RM) $(DESTDIR)$(PREFIX)/bin/dwm $(DESTDIR)$(MANPREFIX)/man1/dwm.1

dist: clean
	tar --create --auto-compress --file=dwm-$(VERSION).tar.zst *
