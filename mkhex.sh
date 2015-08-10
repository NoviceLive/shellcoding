#!/usr/bin/env bash


#
# Copyright 2015 Gu Zhengxiong <rectigu@gmail.com>
#


regex='\t([0-9a-f]{2}\s)+'

if [[ $# -ge 1 ]]
then
    hex=$(objdump -d "$1" | grep -oP $regex)

    if [[ $2 -eq 2 ]]
    then
        printf '# include <stdio.h>\n# include <string.h>\n\n\n'
        printf 'int\nmain(void)\n{\n  '
        printf 'char *shellcode = "'
    fi
    for i in $hex
    do
        if [[ $2 -eq 1 ]]
        then
            fmt='%s'
        else
            fmt='\\x%s'
        fi
        printf $fmt "$i"
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
