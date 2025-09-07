CC      := gcc
CFLAGS  := -Wall -std=c99 -LSDL2 $(shell sdl2-config --cflags)
LDFLAGS := $(shell sdl2-config --libs)

SRC     := $(wildcard src/*.c)

OUTDIR  ?= bin
BIN     := $(OUTDIR)/renderer

$(BIN): $(SRC) | $(OUTDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OUTDIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(OUTDIR)
