#!/usr/bin/env bash


#
# Copyright 2015 Gu Zhengxiong <rectigu@gmail.com>
#


main()
{
    flag=$(parse_args "$@")
    if [[ $? -eq 233 ]]
    then
        show_help
        exit 233
    fi

    regex='\t([0-9a-f]{2}\s)+'
    hex=$(x86_64-w64-mingw32-objdump -d "$1" | grep -oP $regex)
    hex=$(printf '%s' $hex | sed -r 's/(90)*$//g')

    if [[ $flag -ge 2 ]]
    then
        cat <<EOF
/*
 * This file was automatically generated by mkhex.sh,
 * which, together with the complete
 * and heavily commented assembly source code
 * for this shellcode, is available at
 * https://github.com/NoviceLive/shellcoding.
 *
 * For those curious heads
 * striving to figure out what's under the hood.
 */


# include <stdlib.h>
# include <stdio.h>
EOF
        if [[ $flag -eq 3 ]]
        then
            cat <<EOF
# include <stdint.h>

# include <sys/mman.h>
EOF
        fi

        if [[ $flag -eq 4 ]]
        then
            cat <<EOF

# include <windows.h>
EOF
        fi
        cat <<EOF

# define COUNTOF(a) (sizeof(a) / sizeof(a[0]))


int
main(void)
{
EOF
        printf '  char shellcode[] = "'
    fi

    format_hex $hex $flag

    if [[ $flag -ge 2 ]]
    then
        printf '";\n\n'
        if [[ $flag -eq 3 ]]
        then
            cat <<EOF
  int failure = mprotect((void *)((uintptr_t)shellcode & ~4095),
    4096, PROT_READ | PROT_WRITE | PROT_EXEC);

  if (failure) {
    printf ("mprotect\n");
    return EXIT_FAILURE;
  }

EOF
        fi
        if [[ $flag -eq 4 ]]
        then
            cat <<EOF
  DWORD why_must_this_variable;
  BOOL success = VirtualProtect(shellcode, strlen(shellcode),
    PAGE_EXECUTE_READWRITE, &why_must_this_variable);

  if (!success) {
    printf ("VirtualProtect\n");
    return EXIT_FAILURE;
  }

EOF
        fi
        cat <<EOF
  printf("strlen(shellcode)=%d\n", COUNTOF(shellcode));

  ((void (*)(void))shellcode)();

  return EXIT_SUCCESS;
}
EOF
    fi
}

format_hex()
{
    local i=0
    local c=0
    if [[ $2 -eq 1 ]]
    then
        fmt='%s'
    else
        fmt='\\x%s'
    fi
    while [[ $i -lt ${#1} ]]
    do
        if [[ $2 -ge 2 && $c -eq 10 ]]
        then
            c=0
            printf '"\n    "'
        fi

        printf $fmt ${1:$i:2}
        i=$(($i+2))
        c=$(($c+1))
    done
}


show_help()
{
    cat <<EOF
Synopsis: $0 file -e|--escape -r|--raw -c|--c -l|--linux -w|--windows
EOF
}


parse_args()
{
    if [[ $# -lt 1 || (! -f "$1") ]]
    then
        return 233
    fi
    case "$2" in
        -e|--escape)
            flag=0;;
        -r|--raw)
            flag=1;;
        -c|--c)
            flag=2;;
        -l|--linux)
            flag=3;;
        -w|--windows)
            flag=4;;
        *)
            flag=0;;
    esac
    printf '%s' $flag
}


main "$@"
