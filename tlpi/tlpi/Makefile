SRC_FILE = tlpi.c
OUT_FILE = tlpi
SRC_DIR = src/
LIB_FILE = utils/tlpi-book/lib/error_functions.o
INCLUDES = -I./utils/tlpi-book/lib/
OBJ_FILE = $(SRC_FILE:.c=.o)
CC = gcc

all:
	$(CC) $(INCLUDES) -c $(SRC_FILE)
	${CC} -o ${OUT_FILE} ${OBJ_FILE} $(LIB_FILE) 

clean:
	rm *.o $(OUT_FILE)
