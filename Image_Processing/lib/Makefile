LIBS = converters.a
SRC = converters.c
OBJ = converters.o
AR = ar rvs
INCLUDE_DIR = ../include/
CC = gcc -c -I$(INCLUDE_DIR)

clean: $(LIBS)
		rm $(OBJ)

$(LIBS) : $(OBJ)
		$(AR) $(LIBS) $(OBJ)

$(OBJ) : $(SRC)
		$(CC) $(SRC)

