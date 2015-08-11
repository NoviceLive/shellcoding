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

    if [[ $2 -eq 2 ]]
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
        printf '# include <stdio.h>\n# include <string.h>\n\n\n'
        printf 'int\nmain(void)\n{\n  '
        printf 'char *shellcode = "'
    fi

    c=0
    for i in $hex
    do
        if [[ $2 -eq 2 ]] && [[ $c -eq 10 ]]
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

    if [[ $2 -eq 2 ]]
    then
        printf '";\n\n'
        printf '  printf("strlen(shellcode)=%%d\\n"'
        printf ', strlen(shellcode));'
        printf '\n\n  ((void (*)(void))shellcode)();\n\n'
        printf '  return 0;\n}'
    fi

    printf '\n'
else
    printf 'no binaries specified\n'
fi
