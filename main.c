#include <malloc.h>
#include <stdio.h>

#define ALLOC_ESCAPE(x) (x + 1)

typedef struct string
{
  char *_p; // inner string
  int _s;   // the position of the string
} string;

void
string_append (string *s, char z)
{
  char *nfz = s->_p; // save the old string
  s->_p = malloc (ALLOC_ESCAPE (s->_s)
                  + 1);   // allocate a new string with the same length (with 2
                          // extra for the end too)
  s->_p = nfz;            // set the new block to the old saved string
  s->_p[s->_s] = z;       // set the current index to the character
  s->_p[(s->_s) + 1] = 0; // escape it too
  s->_s++;                // update the index
}

void
string1 (string *s)
{
  s->_s = 0;
}

int
main ()
{
  string s;

  string1 (&s); // set index to 0

  string_append (&s, 'h');
  string_append (&s, 'e');
  string_append (&s, 'l');
  string_append (&s, 'l');
  string_append (&s, 'o');

  printf ("%s\n", s._p);
}
