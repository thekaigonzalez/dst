/*Copyright 2019-2023 Kai D. Gonzalez*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string.h"

#define ALLOC_ESCAPE(x) (x + 1)
#define VALIDATE(mem)                                                         \
  if (mem == NULL)                                                            \
    {                                                                         \
      fprintf (stderr, "Memory allocation error\n");                          \
      exit (1);                                                               \
    }

void
str_app (string *s, char z)
{
  s->_p = realloc (s->_p, ALLOC_ESCAPE (str_length (s))
                              + 1); // allocate a new string with the same
                                    // length (with 2 extra bytes)
  VALIDATE (s->_p);
  s->_p[s->__position] = z; // set the current index to the character

  if (z != '\0')
    s->_p[(s->__position) + 1] = 0; // escape it too

  s->__position++; // update the index
}

// sets the string initial positions and memory to 0
// NOTE: keep 1 byte in for an escape just in case things go left field.
void
str_init (string *s)
{
  s->__position = 0;
  s->_p = malloc (1);
  VALIDATE (s->_p);
  s->_p[0] = 0;

  s->__index = 0;

  str_where (s);
}

// puts a string into the structure using string_append()
void
str_xmove (string *s, const char *str)
{
  while (*str)
    {
      str_app (s, *str);
      str++;
    }
}

// str_xmove, except the string is re-initiated before added the new string on
// top of it, allowing you to have a full string instead of that string being
// added onto it
// note: this does NOT replace words in the string
void
str_xmove_replace (string *s, const char *str)
{
  str_init (s);

  str_xmove (s, str);
}

// frees the string
void
str_free (string *s)
{
  free (s->_p);
  str_empty (s); // set everything back to 0
}

// removes the last character in the string and returns it
char
str_pop (string *s)
{
  char n = str_get (s, str_length (s) - 1);

  str_remove (s, str_length (s) - 1);

  return n;
}

int
str_length (string *s)
{
  return s->__position;
}

void
str_remove (string *s, int pos)
{
  VALIDATE (memmove (s->_p + pos, s->_p + pos + 1, str_length (s) - pos));
}

// returns character
char
str_get (string *s, int pos)
{
  if (pos >= str_length (s))
    {
      fprintf (stderr, "Index out of bounds\n");
    };
  return s->_p[pos];
}

char *
str_to_str (string *s)
{
  return s->_p;
}

void
str_cpy (string *dst, string *src)
{
  dst->__position = src->__position;
  dst->_p = malloc (ALLOC_ESCAPE (src->__position));
  VALIDATE (dst->_p);

  memcpy (dst->_p, src->_p, src->__position);
}

int
str_equal (string *s1, string *s2)
{
  if (str_same (s1, s2))
    return 1;
  return 0;
}

int
str_index (string *s)
{
  return s->__index;
}

void
str_next (string *s)
{
  if (str_index (s) < str_length (s))
    {
      s->__index++;
    }
  else
    {
      fprintf (stderr, "Index out of bounds\n");
    }
}

void
str_where (string *s)
{
  s->curr = s->_p[s->__index];
  if (str_exists (s, str_index (s) - 1))
    s->prev = s->_p[s->__index - 1];

  if (str_exists (s, str_index (s) + 1))
    s->next = s->_p[s->__index + 1];
}

int
str_exists (string *s, int index)
{
  return (index < str_length (s) && index >= 0);
}

char
str_current (string *s)
{
  if (str_index (s) < str_length (s))
    return s->_p[s->__index];
}

char
str_prev (string *s)
{
  return (str_exists (s, str_index (s) - 1)) ? s->_p[s->__index - 1] : '\0';
}

char
str_pnext (string *s)
{
  return (str_exists (s, str_index (s) + 1)) ? s->_p[s->__index + 1] : '\0';
}

void
str_print (string *s)
{
  printf ("%s\n", str_to_str (s));
}

void
str_strip_left (string *s)
{
  for (int i = 0; i < str_length (s) - 1; i++)
    {

      if (isspace (s->_p[i]))
        {
          str_remove (s, i);
          i--;
          continue;
        }

      else if (!isspace (s->_p[i]))
        break;
    }
}

void
str_strip_right (string *s)
{
  for (int i = str_length (s) - 1; i > 0; i--)
    {
      if (isspace (s->_p[i]))
        {
          str_remove (s, i);
          continue;
        }
      else if (!isspace (s->_p[i]) && s->_p[i] != '\0')
        break;
    }
}

void
str_strip (string *s)
{
  str_strip_left (s);
  str_strip_right (s);
}

void
str_uppercase (string *s)
{
  for (int i = 0; i < str_length (s); i++)
    s->_p[i] = toupper (s->_p[i]);
}

void
str_lowercase (string *s)
{
  for (int i = 0; i < str_length (s); i++)
    s->_p[i] = tolower (s->_p[i]);
}

void
str_switch_case (string *s)
{
  for (int i = 0; i < str_length (s); i++)
    {
      if (islower (s->_p[i]))
        s->_p[i] = toupper (s->_p[i]);

      else if (isupper (s->_p[i]))
        s->_p[i] = tolower (s->_p[i]);
    }
}

string_list
str_split (string *s, char delim)
{
  int n = 0;

  string_list splits;
  str_list_init (&splits);

  string buffer;
  str_init (&buffer);

  for (int i = 0; i < str_length (s); i++)
    {
      if (s->_p[i] == delim)
        {
        add:
          str_list_add (&splits, &buffer);
          str_empty (&buffer);

          n++;
        }
      else
        {
          str_app (&buffer, s->_p[i]);
        }
    }

  if (str_length (&buffer) != 0)
    {
      goto add;
    }
  return splits;
}

void
str_empty (string *s)
{
  s->__position = 0;
  s->__index = 0;
  s->curr = '\0';
  s->prev = '\0';
  s->next = '\0';
  s->_p = malloc (1);
  s->_p[0] = 0;
}

void
str_list_init (string_list *s)
{
  s->_size = 0;
}

int
str_list_size (string_list *s)
{
  return s->_size;
}

void
str_list_add (string_list *s, string *str)
{
  str_cpy (&s->_list[s->_size], str);

  s->_size++;
}

int
str_same (string *s1, string *s2)
{
  if (str_length (s1) != str_length (s2))
    return 0;

  for (int i = 0; i < str_length (s2) - 1; i++)
    if (str_at (s1, i) != str_at (s2, i))
      return 0;

  return 1;
}

char
str_at (string *s, int pos)
{
  if (pos >= str_length (s))
    fprintf (stderr, "Index out of bounds\n");

  return s->_p[pos];
}
