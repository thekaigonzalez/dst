#include "string.h"

#include <stdio.h>

main ()
{
  string s;      // declare the string
  str_init (&s); // initialize it

  str_xmove (&s, "sTRINGS IN c HAVE NEVER BEEN this easy!"); // move a string into it

  printf("[CURRENT]: %c\n", str_current(&s));
  printf("[NEXT]: %c\n", str_pnext(&s));
  str_next(&s);
  printf("[CURRENT]: %c\n", str_current(&s));
}
