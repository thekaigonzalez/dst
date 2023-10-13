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
str_append_last (string *s, char z)
{
  s->ptr = realloc (s->ptr, ALLOC_ESCAPE (str_length (s))
                                + 1); // allocate a new string with the same
                                      // length (with 2 extra bytes)
  VALIDATE (s->ptr);
  s->ptr[s->__position] = z; // set the current index to the character

  if (z != '\0')
    s->ptr[(s->__position) + 1] = 0; // escape it too

  s->__position++; // update the index
}

// sets the string initial positions and memory to 0
// NOTE: keep 1 byte in for an escape just in case things go left field.
void
str_init (string *s)
{
  // if (s->ptr != NULL) // free the old memory
  //   {
  //     free (s->ptr);
  //   }
  s->__position = 0;
  s->ptr = malloc (1);
  VALIDATE (s->ptr);
  s->ptr[0] = 0;

  s->__index = 0;

  str_where (s);
}

// puts a string into the structure using string_append()
void
str_assign_literal (string *s, const char *str)
{
  while (*str)
    {
      str_append_last (s, *str);
      str++;
    }
}

// str_assign_literal, except the string is re-initiated before added the new
// string on top of it, allowing you to have a full string instead of that
// string being added onto it note: this does NOT replace words in the string
void
str_assign_literal_replace (string *s, const char *str)
{
  str_init (s);

  str_assign_literal (s, str);
}

// frees the string
void
str_free (string *s)
{
  str_void (s);
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
  VALIDATE (memmove (s->ptr + pos, s->ptr + pos + 1, str_length (s) - pos));
  str_pos_move (s, -1);
}

// returns character
char
str_get (string *s, int pos)
{
  if (pos >= str_length (s))
    {
      fprintf (stderr, "Index out of bounds\n");
    };
  return s->ptr[pos];
}

char *
str_to_str (string *s)
{
  return s->ptr;
}

void
str_cpy (string *dst, string *src)
{
  dst->__position = src->__position;
  dst->ptr = malloc (ALLOC_ESCAPE (src->__position));
  VALIDATE (dst->ptr);

  memcpy (dst->ptr, src->ptr, src->__position);
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
  s->curr = s->ptr[s->__index];
  if (str_exists (s, str_index (s) - 1))
    s->prev = s->ptr[s->__index - 1];

  if (str_exists (s, str_index (s) + 1))
    s->next = s->ptr[s->__index + 1];
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
    return s->ptr[s->__index];
}

char
str_prev (string *s)
{
  return (str_exists (s, str_index (s) - 1)) ? s->ptr[s->__index - 1] : '\0';
}

char
str_pnext (string *s)
{
  return (str_exists (s, str_index (s) + 1)) ? s->ptr[s->__index + 1] : '\0';
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

      if (isspace (s->ptr[i]))
        {
          str_remove (s, i);
          i--;
          continue;
        }

      else if (!isspace (s->ptr[i]))
        break;
    }
}

void
str_strip_right (string *s)
{
  for (int i = str_length (s) - 1; i > 0; i--)
    {
      if (isspace (s->ptr[i]))
        {
          str_remove (s, i);
          continue;
        }
      else if (!isspace (s->ptr[i]) && s->ptr[i] != '\0')
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
    s->ptr[i] = toupper (s->ptr[i]);
}

void
str_lowercase (string *s)
{
  for (int i = 0; i < str_length (s); i++)
    s->ptr[i] = tolower (s->ptr[i]);
}

void
str_switch_case (string *s)
{
  for (int i = 0; i < str_length (s); i++)
    {
      if (islower (s->ptr[i]))
        s->ptr[i] = toupper (s->ptr[i]);

      else if (isupper (s->ptr[i]))
        s->ptr[i] = tolower (s->ptr[i]);
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
      if (s->ptr[i] == delim)
        {
        add:
          str_list_add (&splits, &buffer);
          str_void (&buffer);
          str_init(&buffer);
          n++;
        }
      else
        {
          str_append_last (&buffer, s->ptr[i]);
        }
    }

  if (str_length (&buffer) != 0)
    {
      goto add;
    }
  
  str_void(&buffer);

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
  s->ptr = malloc (1);
  s->ptr[0] = 0;
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
  if (&s->_list[s->_size] == NULL)
    return; // the string list is either full or the size isn't correct, one of
            // the two
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

  return s->ptr[pos];
}

void
str_pos_move (string *s, int n)
{
  if (s->__position + n > 0)
    {
      s->__position += n;
    }
}

int
str_null (string *s)
{
  return s->ptr == NULL;
}

string *
str_list_get_at (string_list *s, int index)
{
  if (index >= str_list_size (s))
    return NULL;

  return &s->_list[index];
}

void
str_list_free (string_list *s)
{
  for (int i = 0; i < str_list_size (s); i++)
    {
      str_void (&s->_list[i]);
    }
}

void
str_list_remove (string_list *s, int index)
{
  if (index >= str_list_size (s)) return;

  str_free (&s->_list[index]);
  str_void(&s->_list[index]);
}

void
str_void (string *s)
{
  free (s->ptr);
  s->ptr = NULL;
  s = NULL;
}

string
str_impostor (string *s)
{
  string new;
  str_init (&new);
  str_cpy(s, &new);
  return new;
}

void
str_replace (string *s, char old, char new)
{
  for (int i = 0; i < str_length (s); i++)
    {
      if (s->ptr[i] == old)
        s->ptr[i] = new;
    }
}

void
str_replace_long (string *s, string *old, string *new)
{
  int start = 0;
  if (old == NULL || new == NULL) return;

  for (int i = 0; i < str_length (s); i++) {
    if (start > str_length(old)) {
      break;
    }
    if (str_at(s, i) == old->ptr[start]) {
      str_swap(s, i, new->ptr[start]);
      start++;
    }
  }
}

string*
str_distinct (const char *str)
{
  string* s = malloc (sizeof (string));
  // str_init (s);
  str_assign_literal_replace(s, str);

  return s;
}

void
str_void_ptr (string *s)
{
  free (s->ptr);
  s->ptr = NULL;
  free(s);
  s = NULL;
}

void
str_void_ptr_gc (string *s)
{
  free (s->ptr);
  s->ptr = NULL;
  s = NULL;
}

gc_string
str_gc_empty (void)
{
  string l;
  str_init (&l);
  return l;
}

string *
str_substr (string *s, int start, int end)
{
  string *str = str_distinct("");

  if (start < 0 || end > str_length(s))
    return NULL;

  for (int i = start; i < end; i++)
    str_append_last (str, s->ptr[i]);

  return str;
}

void
str_escape (string *s)
{
  
}

void
str_unescape (string *s)
{
}

void
str_swap (string *s, int i, char j)
{
  if (i > str_length (s)) return;
  s->ptr[i] = j;
}
