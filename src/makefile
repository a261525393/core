SRC = $(notdir $(wildcard ./*.c))
OBJ = $(patsubst %.c,%.o,${SRC})
TARGET = libcore.a

all:
	gcc -g -c ${SRC}
	ar -rc ${TARGET} ${OBJ}

clean:
	rm -rf ${OBJ} ${TARGET}
