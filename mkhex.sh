#!/usr/bin/env bash

#
# I am a bash starter. Feel free to improve
# or adapt this script.
#

#
# Copyright 2015 Gu Zhengxiong <rectigu@gmail.com>
#
# GPL
#


regex='\t([0-9a-f]{2}\s)+'

if [[ $# -ge 1 ]]
then
    hex=$(objdump -d "$1" | grep -oP $regex)

    if [[ $2 -ge 2 ]]
    then
        printf '/*\n * This file was automatically generated'
        printf ' by mkhex.sh,\n * '
        printf 'which, together with the complete\n * '
        printf 'and heavily commented assembly source code\n * '
        printf 'for this shellcode,'
        printf ' is available at\n * '
        printf 'https://github.com/NoviceLive/shellcoding.\n * '
        printf '\n * For those curious heads\n * '
        printf "striving to figure out what's under the hood.\n"
        printf ' *\n */\n\n\n'
        printf '# include <stdio.h>\n# include <string.h>\n'
        if [[ $2 -eq 3 ]]
        then
            printf '# include <stdint.h>\n\n# include <sys/mman.h>\n'
        fi

        if [[ $2 -eq 4 ]]
        then
            printf '\n# include <windows.h>\n'
        fi
        printf '\n\n'
        printf 'int\nmain(void)\n{\n  '
        printf 'char *shellcode = "'
    fi

    c=0
    for i in $hex
    do
        if [[ $2 -ge 2 ]] && [[ $c -eq 10 ]]
        then
            c=0
            printf '"\n    "'
        fi

        if [[ $2 -eq 1 ]]
        then
            fmt='%s'
        else
            fmt='\\x%s'
        fi

        printf $fmt "$i"

        c=$(($c + 1))
    done

    if [[ $2 -ge 2 ]]
    then
        printf '";\n\n'
        if [[ $2 -eq 3 ]]
        then
            printf '  int ret = mprotect ((void *)((uintptr_t)'
            printf 'shellcode & ~4095), 4096,'
            printf '\n    PROT_READ | PROT_WRITE | PROT_EXEC);\n\n'
            printf '  if (ret) {\n'
            printf '    printf ("mprotect\\n");\n'
            printf '    return 1;\n  }\n\n'
        fi

        if [[ $2 -eq 4 ]]
        then
            printf '  DWORD why_must_this_variable;\n'
            printf '  BOOL ret = VirtualProtect (shellcode,'
            printf ' strlen(shellcode),'
            printf '\n    PAGE_EXECUTE_READWRITE, '
            printf '&why_must_this_variable);\n\n'
            printf '  if (!ret) {\n'
            printf '    printf ("VirtualProtect\\n");\n'
            printf '    return 1;\n  }\n'
        fi
        printf '  printf("strlen(shellcode)=%%d\\n"'
        printf ', strlen(shellcode));'
        printf '\n\n  ((void (*)(void))shellcode)();\n\n'
        printf '  return 0;\n}'
    fi

    printf '\n'
else
    printf 'no binaries specified\n'
fi
