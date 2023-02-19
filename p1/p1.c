#include "p1.h"

#define BUFFER 10

/* create a new string variable containing the given char sequence */
/* precondition:  initializer is non-null */
/* precondition:  initializer points to a null-terminated string */
str_t create(char *initializer) {
        // initizal str_t varible
        str_t new_str = NULL;
        int len = 0;
        char *ptr_2 = initializer;
        int i;

        // obtain length of initiailzer
        while(*ptr_2){
                len++;
                ptr_2++;
        }

        // allocate memory for a struct strstr
        new_str = (str_t) malloc(sizeof(struct strstr));

        // allocate memory for the given char sequence
        new_str->ptr = (char *)calloc(len+ BUFFER, sizeof(char));

        // copy char sequence
        // move initializer ptr back to beginning of array
        for(i = 0; i < len; i++){
                new_str->ptr[i] = initializer[i];
        }

        new_str->str_capacity = len + BUFFER;
        new_str->str_len = len;

        return new_str;
}

/* return the length of the string */
/* precondition: s has been initialized (created) */
int length(str_t s) {
        // find length of s
        return s->str_len;
}

/* return 1 if s1 and s2 represent the same string, 0 otherwise  */
/* precondition:  both arguments are non-NULL */
int equals(str_t s1, str_t s2) {
        int i;
        if(length(s1) != length(s2)){
                return 0;
        }
        else{
                // s1 & s2 are same length
                // go through str_t and make sure that s1 = s1
                for(i = 0; i < length(s1);i++){
                        if(s1->ptr[i] != s2->ptr[i]){
                                return 0;
                        }
                }
                return 1;
        }
}


/* make the contents of "to" be the contents of "from" */
/* precondition: both are valid (initialized) strings */
void copy(str_t to, str_t from) {
        int i;

        // copy sequence
        // if the max capacity of to is not large enough to copy
        if(to->str_capacity < from->str_len){
                to->ptr = (char)realloc(to->ptr, from->str_capacity);
                to->str_capacity = from->str_capacity;
        }
        else if(length(to) > length(from)){
                for(i=0; i < length(to); i++){
                        to->ptr[i] = 0;
                }
        }
        for(i = 0; i < length(from); i++){
                to->ptr[i] = from->ptr[i];
        }
        to->ptr[length(from)] = 0;
        to->str_len = from->str_len;
}

/* modify
 * the contents of the first argument by replacing every
 * character in it that also occurs in the second argument with a
 * space character (integer value \verb.0x20.).  In other words,
 * this has the same semantics as the corresponding function in Project 0.
 */
void censor(str_t orig, str_t bad) {
        int i;
        int j;
        for(j = 0; j < length(orig); j++){
                for(i = 0; i < length(bad); i++){
                        if((orig->ptr[j]) == (bad->ptr[i])){
                                orig->ptr[j] = 0x20;
                        }
                }
        }
}

/* return a pointer to a character array that contains
 * the same sequence of characters as s, but with the end marked by a
 * null (0) byte, according to the C convention.
 * Subsequent changes to s may change the returned C string, including modifying
 * the end marker.  This is intended for ephemeral, one-time use, e.g.,
 * passing to printf().
 */
char *to_chars(str_t s) {
        return s->ptr;
}

/* Extend string s1 by appending the string s2 to it.  s2 is unmodified. */
void append(str_t s1, str_t s2) {
        int i;
        int sum = s1->str_len + s2->str_len;
        if(s1->str_capacity < sum){
                s1->ptr = (char*)realloc(s1->ptr, sum + BUFFER);
                s1->str_capacity = sum + BUFFER;
        }
        for(i = 0; i < length(s2); i++){
                s1->ptr[length(s1) + i] = s2->ptr[i];
        }
        s1->ptr[sum] = '\0';
        s1->str_len = sum;
}

/* Return a new string of len characters equal to the len characters of s
 * beginning at position start.  The  original string s is unchanged.
 * If start + len exceeds the actual length of the string, the
 * returned string consists of the characters from index start to the end of s.
 * Precondition: both start and len are at least 0.
 */
str_t substring(str_t s, int start, int len) {
  str_t str_new = create("");
  int i = 0;
  int current_pos = 0;
  int sum = start + len;

  str_new->str_len = len;
  // allocated len amount of space for the substring
  str_new->ptr = (char *)realloc(str_new->ptr, len + BUFFER);
  str_new->str_capacity = len + BUFFER;

  for(i = 0; i < sum; i++){
          if(i < start){
                  continue;
          }
          else if(i > s->str_len){
                  break;
          }
          else{
                  str_new->ptr[current_pos] = s->ptr[i];
                  current_pos++;
          }
  }
  return str_new;
}
