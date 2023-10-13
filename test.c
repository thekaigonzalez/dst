#include "string.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define PASSED printf ("passed %s\n", __func__)
#define FAILED                                                                \
  printf ("failed %s\n", __func__);                                           \
  exit (-1)

static void
test_str_init (void)
{
  string s;
  str_init (&s);

  assert (str_length (&s) == 0);
  assert (str_current (&s) == '\0');
  assert (str_to_str (&s) != NULL);

  PASSED;
  str_free (&s);
}

static void
test_str_basic (void)
{
  string s;
  str_init (&s);

  str_append_last (&s, 'a');
  str_append_last (&s, 'b');
  str_append_last (&s, 'c');
  str_append_last (&s, 'd');

  assert (str_length (&s) == 4);
  assert (str_current (&s) == 'a');
  assert (str_pnext (&s) == 'b');

  assert (str_pop (&s) == 'd');
  assert (str_length (&s) == 3);

  PASSED;
  str_free (&s);
}

static void
test_str_macro (void)
{
  STRING (sample);
  assert (str_length (&sample) == 0);
  assert (str_current (&sample) == '\0');
  PASSED;
  str_free (&sample);
}

static void
test_str_strip (void)
{
  STRING (sample);
  str_strip_right (&sample);
  str_strip_left (&sample);

  assert (str_length (&sample) == 0);

  str_assign_literal (&sample, "  hello  ");

  assert (str_length (&sample) == 9);

  str_strip (&sample);

  assert (str_length (&sample) == 5);
  PASSED;
  str_free (&sample);
}

static void
test_str_out_of_bounds (void)
{
  STRING (sample);

  str_remove (&sample, 0);

  assert (str_length (&sample) == 0);

  str_remove (&sample, 0);
  str_remove (&sample, 0);
  str_remove (&sample, 0);

  assert (str_length (&sample) == 0);

  PASSED;
  str_free (&sample);
}

static void
test_str_is_null (void)
{
  string s;
  str_init (&s);
  assert (!str_null (&s));
  str_free (&s);
  assert (str_null (&s));
  PASSED;
}

static void
test_str_list (void)
{
  string_list s;
  str_list_init (&s);

  assert (str_list_size (&s) == 0);

  STRING (member1);
  str_assign_literal (&member1, "member 1");
  STRING (member2);
  str_assign_literal (&member2, "member 2");

  str_list_add (&s, &member1);
  str_list_add (&s, &member2);

  assert (str_list_size (&s) == 2);

  str_list_free (&s);
  PASSED;
  str_free (&member1);
  str_free (&member2);
}

static void
test_str_void (void)
{
  STRING (sample);
  str_void (&sample);

  assert (str_length (&sample) == 0);
  assert (str_null (&sample));

  PASSED;
  str_free (&sample);
}

static void
test_str_split (void)
{
  STRING (sample);
  str_assign_literal (&sample, "hello world");

  string_list list = str_split (&sample, ' ');

  assert (str_list_size (&list) == 2);

  string *member1 = str_distinct ("hello");
  string *member2 = str_distinct ("world");

  assert (str_equal (str_list_get_at (&list, 0), member1));
  assert (str_equal (str_list_get_at (&list, 1), member2));

  PASSED;
  str_void (&sample);
  str_void_ptr (member1);
  str_void_ptr (member2);
  str_list_free (&list);
}

static void
test_gc_string (void)
{
  gc_string l = str_gc_empty ();

  str_assign_literal (&l, "hello");
  str_append_last (&l, 'a');

  assert (str_length (&l) == 6);
  PASSED;
}

static void
test_sub_string (void)
{
  string *sample = str_distinct ("hello");
  string *sample_substring = str_substr (sample, 1, 4);

  assert (str_length (sample_substring) == 3);

  str_void_ptr (sample);
  str_void_ptr (sample_substring);

  PASSED;
}

static void test_long_replace(void) {
  string *s = str_distinct("hello");
  string *torep = str_distinct("he");
  string *new = str_distinct("je");
  
  string *result = str_distinct("jello");

  str_replace_long(s, torep, new);

  assert (str_length(s) == 5);
  assert (str_equal(s, result));

  str_void_ptr(s);
  str_void_ptr(torep);
  str_void_ptr(new);
  str_void_ptr(result);

  PASSED;
}

int
main (void)
{
  test_str_init ();
  test_str_basic ();
  test_str_macro ();
  test_str_strip ();
  test_str_out_of_bounds ();
  test_str_is_null ();
  test_str_list ();
  test_str_void ();
  test_str_split ();
  test_gc_string ();
  test_sub_string ();
  test_long_replace();

  return 0;
}
