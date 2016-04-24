#include <stdio.h>

int main(int argc, char* argv[])
{
  int offset = 0;
  int ch;
  printf("%5d ", offset);
  while ( (ch = getchar()) != EOF)
  {
    putchar(ch);
    ++offset;
    if (ch == '\n')
      printf("%5d ", offset);
  }
  return 0;
}
