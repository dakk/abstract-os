mov eax, 123
mov ebx, 123
mov ecx, 123
mov edx, 123
int 0x80

jmp $

  mov eax, 0xA1
  mov ebx, hello_str
  int 0x80
  jmp $

hello_str:
  db "Hello, World!", 0x0A, 0x00
