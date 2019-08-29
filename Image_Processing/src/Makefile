CC = gcc -o
EXE = histogram
LIBS = converters.a
LIB_DIR = ../lib/
INCLUDE_DIR = ../include/
BIN_DIR = ../bin/
CFLAGS = `pkg-config --cflags --libs MagickWand` -lm

$(EXE)_e : $(EXE).c
		#gcc -o ../bin/calculadora_e calculadora.c ../lib/lib_math.a -I../include/
		$(CC) $(BIN_DIR)$(EXE) $(EXE).c $(LIB_DIR)$(LIBS) -I$(INCLUDE_DIR) $(CFLAGS)


