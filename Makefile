DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin
DIR_LIB = ./lib

SRC = $(wildcard ${DIR_SRC}/*.c) $(wildcard ${DIR_LIB}/cJSON/*.c)
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC}))

TARGET = qq

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc
CFLAGS = -g -O2 -Wall -Wextra -I${DIR_INC} -I${DIR_LIB}

${BIN_TARGET}:${OBJ}
	$(CC) $(CFLAGS) $(OBJ)  -o $@ -lcurl

${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	$(CC) $(CFLAGS) -c  $< -o $@

${DIR_OBJ}/cJSON.o:${DIR_LIB}/cJSON/cJSON.c
	$(CC) $(CFLAGS) -c  $< -o $@

.PHONY:clean

clean:
	rm -rf ${DIR_OBJ}/*.o
	rm -rf ${BIN_TARGET}
