SRC = $(wildcard *.c)
TARGET = $(patsubst %.c,%.t,${SRC})

${TARGET}:${SRC}
	gcc -g -rdynamic ${SRC} -L../src -lcore -o ${TARGET}

clean:
	rm -rf ${TARGET}
