CC = gcc
LD = gcc

GTK_VERSION = 3.0

INCS = $(shell pkg-config --cflags gtk+-$(GTK_VERSION)) -I$(PWD)/../libnubix/
LIBS = $(shell pkg-config --libs gtk+-$(GTK_VERSION)) -lpam -pthread -L/usr/X11R6/lib -lX11

LDFLAGS = $(LIBS) -lpam
CFLAGS = -std=gnu11

BIN = nubix-desktop.o

#check_mode:
#	ifdef $(BUILD_MODE)
#		ifeq ($(BUILD_MODE),debug)
#			CFLAGS += -ggdb3
#		else ifeq ($(BUILD_MODE),run)
#			CFLAGS += -O2
#		else
#			$(warning Build mode setting to default.)
#		endif
#	endif

# all: check_mode $(OBJ)
all: $(BIN)

%.o: %.c
	$(CC) $(INCS) $(CFLAGS) $<  $(PWD)/../libnubix/libnubix.a  -o $@ $(LIBS)

.PHONY: clean all

clean:
	rm -f $(BIN)
