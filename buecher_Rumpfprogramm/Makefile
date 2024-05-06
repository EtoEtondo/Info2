CC = gcc

INCDIR = ./list
CPPFLAGS = -I${INCDIR}
CFLAGS = -g -Wall
#CFLAGS = -g0 -O3

OBJS = buecher.o buecher_func.o
LOBJS = ${INCDIR}/list.o
EXE = buecher

${EXE}: ${OBJS} list_obj
	${CC} -o $@ ${OBJS} ${LOBJS}

${OBJS}: buecher_func.h ${INCDIR}/list.h

list_obj:
	cd ${INCDIR}; ${MAKE} all "CC=${CC}" "CFLAGS=${CFLAGS}"

run: ${EXE}
	./${EXE}

clean:
	/bin/rm -f core *.o; cd ${INCDIR}; ${MAKE} clean

