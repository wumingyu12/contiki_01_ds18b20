CONTIKI_PROJECT = ds18b20-example

PROJECT_SOURCEFILES+=ds18b20.c

all: $(CONTIKI_PROJECT)

CONTIKI = ../..
include $(CONTIKI)/Makefile.include
