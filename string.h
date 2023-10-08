/*Copyright 2019-2023 Kai D. Gonzalez*/

#ifndef __STRING_H
#define __STRING_H

typedef struct string
{
  char *_p; // inner string
  int _s;   // the position of the string
} string;

void string_append (string *s, char z);

void string1 (string *s);

void puts (string *s, const char *str);

#endif
