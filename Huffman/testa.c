
#include <stdio.h>
void main()
{
  char a;
  int b;
  int c;
  char *ptr;  // declara um ponteiro para um inteiro
  int *ptr2;  // um ponteiro para uma variável do tipo inteiro
  
  a = 'a';
  b = 2;
  c = 3;
  ptr = &a;
  ptr2 = &b;
  printf("Valor de ptr: %p, Conteúdo de ptr: %c\n", ptr, *ptr);
  printf("Valor de ptr: %p, Conteúdo de ptr: %d\n", ptr2, *ptr2);
  printf("A: %c, B: %d, C: %d", b, c);
}