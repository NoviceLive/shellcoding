# Shellcoding

## Programs

### [runhex.c](./runhex.c)

Executing C-style hex-escaped string data on the stack.

## Scripts

### [mkhex.sh](./mkhex.sh)

Extracting shellcode from binaries
and / or constructing a C source file for testing purposes.

## Linux Shellcode

- [exit IA32 7 Bytes Null-Free](./linux/exit/expert.s)

- [execve /bin/sh IA32 21 Bytes Null-Free](./linux/sh/push.s)

- [execve /bin/sh AMD64 23 Bytes Null-Free](./linux/sh/push64.s)

## Windows Shellcode

- [user32!MessageBoxA "Hello World!" All x86 Windows 199 Bytes Null-Free](./windows/messagebox/messagebox32.asm)
