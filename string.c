/*Copyright 2019-2023 Kai D. Gonzalez*/

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "string.h"

#define ALLOC_ESCAPE(x) (x + 1)

void
string_append (string *s, char z)
{
  s->_p = realloc (
      s->_p, ALLOC_ESCAPE (strlen (s->_p))
                 + 1);    // allocate a new string with the same length (with 2
  s->_p[s->_s] = z;       // set the current index to the character
  s->_p[(s->_s) + 1] = 0; // escape it too
  s->_s++;                // update the index
}

void
string1 (string *s)
{
  s->_s = 0;
  s->_p = malloc (1);
  s->_p[0] = 0;
}

// puts a string into the structure using string_append()
void puts(string* s, const char* str) {
  while (*str) {
    string_append(s, *str);
    str++;
  }
}
