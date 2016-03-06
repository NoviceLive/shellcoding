#!/usr/bin/env zsh


#
# Copyright 2015 Gu Zhengxiong <rectigu@gmail.com>
#


if [[ $# -ne 1 ]]
then
    printf '%s\n' 'Invalid Argument!'
    exit 233
fi


objdump -D -b binary -m i386:x86-64 -M intel =(unhex $1)
