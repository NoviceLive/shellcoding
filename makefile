runhex64: runhex64.o
	gcc -m64 -o runhex64 runhex64.o


runhex32: runhex32.o
	gcc -m32 -o runhex32 runhex32.o


runhex64.o: runhex.c
	gcc -m64 -std=c99 -c runhex.c -o runhex64.o


runhex32.o: runhex.c
	gcc -m32 -std=c99 -c runhex.c -o runhex32.o


clean:
	rm -rf runhex32 runhex64 runhex32.o runhex64.o


test:
	./runhex32 '\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80'
	./runhex64 '\x31\xf6\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x56\x53\x54\x5f\x6a\x3b\x58\x31\xd2\x0f\x05'


install:
	ln -srf ./runhex32 ~/lnk/runhex32
	ln -srf ./runhex64 ~/lnk/runhex64
	ln -srf ./mkhex.sh ~/lnk/mkhex
