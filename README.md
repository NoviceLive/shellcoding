# Shellcoding


## Programs


### [runbin.c](./utils/runbin.c)

Executing data on the stack, which is used to test and debug shellcode.

Prebuilt binaries exist both for Windows and Linux.

#### Usage

```
./bin/runbin -h
Usage: runbin [-e] <filename>

    -h, --help    show this help message and exit
    -e, --escape  Use escape mode.
```

#### Examples

```
$ hexdump 64.bin
0000000 f631 bb48 622f 6e69 2f2f 6873 5356 5f54
0000010 3b6a 3158 0fd2 0005
0000017
$ runbin 64.bin
[-] Printing memory: 0x7ffda9515640 23
31 f6 48 bb 2f 62 69 6e 2f 2f 73 68 56 53 54 5f
6a 3b 58 31 d2 0f 05
[-] Executing address: 0x7ffda9515640
[toor@bogon shellcoding.git]$ exit
exit
$ less -FX 64.txt                                                                               :(
\x31\xf6\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x56\x53\x54\x5f\x6a\x3b\x58\x31\xd2\x0f\x05
$ runbin -e 64.txt
[-] Printing memory: 0x7ffde32e3590 23
31 f6 48 bb 2f 62 69 6e 2f 2f 73 68 56 53 54 5f
6a 3b 58 31 d2 0f 05
[-] Executing address: 0x7ffde32e3590
[toor@bogon shellcoding.git]$ exit
exit
```


## Scripts


### [mkhex.sh](./historic/mkhex.sh)

This is deprecated
and [IntelliCoder] is strongly recommended for the time being.

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


[IntelliCoder]: https://github.com/NoviceLive/intellicoder
