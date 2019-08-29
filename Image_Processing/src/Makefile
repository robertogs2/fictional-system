CC = gcc -o
HISTOGRAM = histogram
CLASSIFICATOR = classificator
LIBS = converters.a
LIB_DIR = ../lib/
INCLUDE_DIR = ../include/
BIN_DIR = ../bin/
CFLAGS = `pkg-config --cflags --libs MagickWand` -lm

all: $(HISTOGRAM) $(CLASSIFICATOR)

$(HISTOGRAM) : $(HISTOGRAM).c

		$(CC) $(BIN_DIR)$(HISTOGRAM) $(HISTOGRAM).c $(LIB_DIR)$(LIBS) -I$(INCLUDE_DIR) $(CFLAGS)

$(CLASSIFICATOR) : $(CLASSIFICATOR).c

		$(CC) $(BIN_DIR)$(CLASSIFICATOR) $(CLASSIFICATOR).c $(CFLAGS)


