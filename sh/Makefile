SS = push pop

all:
	for i in $(SS); \
	do \
		as --32 "$$i".s && ld -m elf_i386 -o "$$i" a.out; \
		rm -f a.out; \
	done

strace: all
	for i in $(SS); \
	do \
		strace ./"$$i"; \
	done

shellcode: all
	for j in $(SS); \
	do \
		printf 'char *shellcode = "'; \
		for i in $$(objdump -d "$$j" | grep -oP '\t\K.+\t'); \
		do \
			printf "\\\x$$i"; \
		done; \
		printf '";\n'; \
	done

c: all
	for j in $(SS); \
	do \
		printf '#include <stdio.h>\n#include <string.h>\n\n' > "$$j".c; \
		printf 'int\nmain(void)\n{\n  ' >> "$$j".c; \
		printf 'char *shellcode = "' | tee -a "$$j".c; \
		for i in $$(objdump -d "$$j" | grep -oP '\t\K.+\t'); \
		do \
			printf "\\\x$$i" | tee -a "$$j".c; \
		done; \
		printf '";\n\n' | tee -a "$$j".c; \
		printf '  printf("strlen(shellcode)=%%d\\n"' >> "$$j".c; \
		printf ', strlen(shellcode));' >> "$$j".c; \
		printf '\n\n  ((void (*)(void))shellcode)();\n\n' >> "$$j".c; \
		printf '  return 0;\n}\n' >> "$$j".c; \
	done

test: c
	for i in $(SS); \
	do \
		gcc -m32 -z execstack -g -o "$$i"-test "$$i".c; \
	done

clean:
	for i in $(SS); \
	do \
		rm -f "$$i" "$$i".c "$$i"-test; \
	done
