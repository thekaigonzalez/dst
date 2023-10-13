/*Copyright 2019-2023 Kai D. Gonzalez*/

#ifndef __STRING_H
#define __STRING_H

typedef struct string
{
  char *ptr;      // inner string
  int __position; // the position of the string

  int __index; // the index of the current character
  char curr;   // the current character
  char prev;   // the previous character
  char next;   // the next character
} string;

typedef struct string_list
{
  string _list[100];
  int _size;
} string_list;

#define STRING(name)                                                          \
  string name;                                                                \
  str_init (&name);

#define ERROR(msg) fprintf (stderr, "%s\n", msg);

// a string that uses cleanup to automatically be freed
#define gc_string string __attribute__((cleanup(str_void_ptr_gc)))
#define gc_strptr gc_string *

// add a character to the string
void str_append_last (string *s, char z);

/// @brief initializes the string
/// @param s
void str_init (string *s);

// adds *str into the string (can also be used as a concatenate feature if
// string isn't cleared, to clear them use str_assign_literal_replace())
void str_assign_literal (string *s, const char *str);

// adds *str into the string, replacing the current string
void str_assign_literal_replace (string *s, const char *str);

// frees the string
void str_free (string *s);

// removes the last character from the string
char str_pop (string *s);

// returns the length of the string
int str_length (string *s);

// removes a character at POS in the string
void str_remove (string *s, int pos);

// gets character at position in the string
char str_get (string *s, int pos);

// returns the string as a char*
char *str_to_str (string *s);

// copies a string into another string
void str_cpy (string *dst, string *src);

// checks if one string is equal to another
int str_equal (string *s1, string *s2);

// returns the current index
int str_index (string *s);

// moves to the next character
void str_next (string *s);

// checks the next and previous characters, also updating the current
// character
void str_where (string *s);

// checks if the index exists in the string
int str_exists (string *s, int index);

// returns the current character at the token index
char str_current (string *s);

// returns the previous character
char str_prev (string *s);

// returns the next character
char str_pnext (string *s);

// prints a string
void str_print (string *s);

// strips the left side of the string
void str_strip_left (string *s);

// strips the right side of the string
void str_strip_right (string *s);

// strips the left and right side of the string
void str_strip (string *s);

// will convert the string to uppercase
void str_uppercase (string *s);

// will convert the string to lowercase
void str_lowercase (string *s);

// switches the case of the string (turns lower case to upper case and vice
// versa)
void str_switch_case (string *s);

// splits the string into an array of strings
string_list str_split (string *s, char delim);

// sets the string to empty
void str_empty (string *s);

// starts a string list
void str_list_init (string_list *s);

// returns the size of the string list
int str_list_size (string_list *s);

/**
 * Add a string to a string_list structure.
 *
 * This function adds a string to a string_list structure. It copies the
 * content of the provided string into the string_list and increments the
 * size of the list. It's typically used to store a collection of strings in
 * the string_list.
 *
 * @param s Pointer to the string_list structure where the string will be
 * added.
 * @param str Pointer to the string to be added to the string_list.
 */
void str_list_add (string_list *s, string *str);

/**
 * Compare two string objects for equality.
 *
 * This function compares two string objects and checks if they have the same
 * content. It returns 1 if the strings are identical and 0 if they are not.
 *
 * @param s1 Pointer to the first string object.
 * @param s2 Pointer to the second string object to compare.
 *
 * @return 1 if the strings are the same, 0 if they are different.
 */
int str_same (string *s1, string *s2);

// return char at position
char str_at (string *s, int pos);

// adds n to the position
void str_pos_move (string *s, int n);

// checks if the string is null
int str_null (string *s);

// returns the string at the index
string *str_list_get_at (string_list *s, int index);

// frees all the strings in a list
void str_list_free (string_list *s);

// removes a string at the index
void str_list_remove (string_list *s, int index);

// completely and utterly deletes a string; this is NOT str_empty, this function
// turns the string NULL meaning it takes up no bytes AT ALL while str_empty
// turns everything in the function to either 0 or an empty byte, simply
// restarting the string itself
void str_void (string *s);

// impostor will create a string that is the exact same as the string you pass in
string str_impostor (string *s);

// replaces every instance of a character in a string with another character
void str_replace (string *s, char old, char new);

// replaces every instance of a string in a string with another string
void str_replace_long (string *s, string *old, string *new);

// creates a basic new string allocated immediately for use
string *str_distinct (const char *str);

// frees a string object created by str_distinct
void str_void_ptr (string *s);

// frees a gc string pointer created by str_distinct
void str_void_ptr_gc (string *s);

// allows a gc string to be initialized
gc_string str_gc_empty (void);

// extracts a substring from a string
string *str_substr (string *s, int start, int end);

// turns escaped escapes into escapes
void str_escape (string *s);

// turns escapes into escaped escapes
void str_unescape (string *s);

// swaps character at index for another
void str_swap (string *s, int i, char j);
#endif
