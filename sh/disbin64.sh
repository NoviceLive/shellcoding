#!/usr/bin/env bash


#
# Copyright 2015-2016 Gu Zhengxiong <rectigu@gmail.com>
#


if [[ $# -ne 1 ]]; then
    printf '%s\n' 'Required argument: raw binary to be disassembled!'
    exit 1
fi


objdump -D -b binary -m i386:x86-64 -M intel "${1}" | less -FXR
