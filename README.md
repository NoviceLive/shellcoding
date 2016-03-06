# Shellcoding


## Programs


### [runbin.c](./utils/runbin.c)

Executing C-style hex-escaped string data on the stack.

Prebuilt binaries exist both for Windows and Linux.


## Scripts


### [mkhex.sh](./historic/mkhex.sh)

This is deprecated.

Extracting shellcode from binaries
and / or constructing C source code for demonstration or testing.


### [dishex32.sh](./sh/dishex32.sh) / [dishex64.sh](./sh/dishex64.sh)

Disassembling the given hex string using `objdump`.

Z Shell must be installed due to the use of `=()`.

For example:

```bash
./dishex64.sh cccccccc
```


## Linux Shellcode

- [exit IA32 7 Bytes Null-Free](./linux/exit/expert.s)

- [execve /bin/sh IA32 21 Bytes Null-Free](./linux/sh/push.s)

- [execve /bin/sh AMD64 23 Bytes Null-Free](./linux/sh/push64.s)


## Windows Shellcode

- [user32!MessageBoxA "Hello World!" All x86 Windows 199 Bytes Null-Free](./windows/messagebox/messagebox32.asm)


## Documentation

- [对照内核结构深入理解动态定位 API](./doc/api-res-zh_CN.md)
