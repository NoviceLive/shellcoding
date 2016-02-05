FLAGS = -Wall
CC64 = gcc -m64 ${FLAGS}
CC32 = gcc -m32 ${FLAGS}
WINCC64 = x86_64-w64-mingw32-gcc ${FLAGS}
WINCC32 = i686-w64-mingw32-gcc ${FLAGS}
BINDIR = bin


all:
	make runhex64
	make runhex32
	make windows


runhex64: runhex64.o
	${CC64} -o ${BINDIR}/runhex64 ${BINDIR}/runhex64.o


runhex32: runhex32.o
	${CC32} -o ${BINDIR}/runhex32 ${BINDIR}/runhex32.o


windows: runhex.c
	${WINCC64} runhex.c -o ${BINDIR}/runhex64.exe
	${WINCC32} runhex.c -o ${BINDIR}/runhex32.exe


runhex64.o: runhex.c
	${CC64} -c runhex.c -o ${BINDIR}/runhex64.o


runhex32.o: runhex.c
	${CC32} -c runhex.c -o ${BINDIR}/runhex32.o


test:
	./${BINDIR}/runhex32 '\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80'
	./${BINDIR}/runhex64 '\x31\xf6\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x56\x53\x54\x5f\x6a\x3b\x58\x31\xd2\x0f\x05'


install: runhex64 runhex32
	sudo cp ./${BINDIR}/runhex32 /usr/bin/runhex32
	sudo cp ./${BINDIR}/runhex64 /usr/bin/runhex64
	sudo ln -srf /usr/bin/runhex64 /usr/bin/runhex

	sudo cp ./mkhex.sh /usr/bin/mkhex

	sudo cp ./dishex32.sh /usr/bin/dishex32
	sudo cp ./dishex64.sh /usr/bin/dishex64
	sudo ln -srf /usr/bin/dishex64 /usr/bin/dishex


clean:
	rm -rf ${BINDIR}/{runhex32,runhex64,*.o,*.exe}
