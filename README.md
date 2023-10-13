<!--Copyright 2019-2023 Kai D. Gonzalez-->

# dst - The NEW String Library for c

```c
#include "string.h"
STRING (sample);
str_assign_literal (&sample, "hello world");

string_list list = str_split (&sample, ' ');

assert (str_list_size (&list) == 2);

string *member1 = str_distinct ("hello");
string *member2 = str_distinct ("world");

assert (str_equal (str_list_get_at (&list, 0), member1));
assert (str_equal (str_list_get_at (&list, 1), member2));

str_void (&sample);
str_void_ptr (member1);
str_void_ptr (member2);
str_list_free (&list);
```

this is the new, modern, and cleanest string library for c in the world. *(not
really yet but it will be VERY VERY SOON)*

it contains a lot of new
features such as:

* string functions
* string lists
* string stripping
* and string splitting

each function works off of another, so it is
very easy to use and understand. **this library is a WORK IN PROGRESS**,
however, it's main header file is very commented and contains useful
explanations for each function.

This string library is dynamic, so it is able to grow in size as
well as shrink. This library is also very portable.

> Compliant with most C standards, tested with TCC and GCC on Linux.

## dst - Lexical Analysis

this string library also comes with a built in lexical analysis
algorithm, using `str_next(), str_where(), str_exists(), and
str_index()`. if you want to use the library you need to include the LOCAL
string.h header (not the glib one) and build the string.c file with
your project. there is quick compilation so performance won't be a
problem, and you are easily able to free all the memory used by the
string with free().

Here is an example *using* the lexicon functions in DST.

```c
#include "string.h"

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
```

```text
[CURRENT]: s
[NEXT]: T
[CURRENT]: T
```

* **NOTE**: view the function list in functions.TXT

## dst - License

```txt
            this project is licensed under the gnu agpl 3.0

            any questions, suggestions, why the hell did you make this terrible
            program? contact me! also please refer to my old string libraries to
            learn how this library works as well.

            <gkai70263@gmail.com>
```
