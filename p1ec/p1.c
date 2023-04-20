/*
Disclaimer: this is the solution for p1, p1.c provided by the professor
  - Last Edited: 04/20/2023
  - Changes: defined destroy() and edit() functions for extra credit
 Notes: edit(aa, bbb, aaaaa) -> bbbbbba [current: aaaaa->bbbbb]
        edit(hyper, <empty string>, hypermobility) -> mobility [current: ]
        edit(the, not the, Now is the time for all good men to come to the aid of their party.) 
            -> Now is not the time for all good men to come to not the aid of their party.
            [current: ]

*/


#include "p1.h"
#include <malloc.h>
/* invariants:
 *  strt_capacity >= strt_length
 *  strt_length is the number of valid chars in strt_content[]
 */
#define DFLTCAP 128
#define EXTRA 16

/* create a new string variable containing the given char sequence */
/* precondition:  initializer is non-null */
/* precondition:  initializer points to a null-terminated string */
str_t create(char *initializer) {
  /* determine the length of the C-style argument */
  int cap = DFLTCAP;
  int l = 0;
  int need = EXTRA;
  while (initializer[l])
    l++;
  need += l;
  while (need > cap)
    cap <<= 1;  // double the capacity
  str_t newone = malloc(sizeof(struct strstr));
  newone->strt_length = l;
  newone->strt_capacity = cap;
  newone->strt_content = malloc(cap);
  char *cp = newone->strt_content;
  for (int i=0; i<l; i++)
    cp[i] = initializer[i];
  return newone;
}

/* return the length of the string */
/* precondition: s has been initialized (created) */
int length(str_t s) {
  return s->strt_length;
}

/* return 1 if s1 and s2 represent the same string, 0 otherwise  */
/* precondition:  both arguments are non-NULL */
int equals(str_t s1, str_t s2) {
  if (s1->strt_length != s2->strt_length)
    return 0;
  /* s1 and s2 are the same length */
  for (int i=0; i<s1->strt_length; i++)
    if (s1->strt_content[i] != s2->strt_content[i])
      return 0;
  return 1;
}

/* make the contents of "to" be the contents of "from" */
/* precondition: both are valid (initialized) strings */
void copy(str_t to, str_t from) {
  int i;
  /* do we have enough capacity? */
  int need = from->strt_length + EXTRA;
  while (need > to->strt_capacity)
    // increase by standard increments
    to->strt_capacity += DFLTCAP;
  /* tp->strt_capacity >= from->strt_length + EXTRA */
  to->strt_content = realloc(to->strt_content,to->strt_capacity);
  to->strt_length = from->strt_length;
  for (i=0; i<to->strt_length; i++)
    to->strt_content[i] = from->strt_content[i];
}

/* modify the contents of the first argument by replacing every
 * character in it that also occurs in the second argument with a
 * space character (integer value 0x20).  In other words,
 * this has the same semantics as the corresponding function in Project 0.
 */
void censor(str_t orig, str_t bad) {
  int i, j;
  for (i=0; i < orig->strt_length; i++)
    for (j=0; j < bad->strt_length; j++)
      if (orig->strt_content[i] == bad->strt_content[j])
        orig->strt_content[i] = ' ';
}

/* return a pointer to a character array that contains
 * the same sequence of characters as s, but with the end marked by a
 * null (0) byte, according to the C convention.
 * Subsequent changes to s may change the returned C string,
 * including modifying the end marker.
 * This is intended for ephemeral, one-time use, e.g.,
 * passing to printf().
 */
char *to_chars(str_t s) {
  /* We just add a null-terminator and return a pointer to current content
   * pointer.
   */
  if (s->strt_capacity == s->strt_length) { // no room for null
    /* XXX paranoia - this should not happen */
    s->strt_content = realloc(s->strt_content,s->strt_length + EXTRA);
  }
  /* s->strt_content has at least one byte beyond the current string */
  s->strt_content[s->strt_length] = 0;
  return s->strt_content;
}

/* Extend string s1 by appending the string s2 to it.  s2 is unmodified. */
void append(str_t s1, str_t s2) {
  int i,j;
  /* first figure out how much space we need */
  int size = s1->strt_capacity;
  int needed = s1->strt_length + s2->strt_length + EXTRA;
  if (size < needed) {  /* do we need to allocate more space? */
    do {  /* yes - figure out how much */
      size += DFLTCAP;
    } while (size < needed);
    /* size >= needed */
    s1->strt_content = realloc(s1->strt_content,size);
    s1->strt_capacity = size;
  }
  /* where to copy */
  size = s1->strt_length + s2->strt_length;
  /* size is now the length of s1 after appending */
  for (i=s1->strt_length, j=0; i < size; i++, j++)
    s1->strt_content[i] = s2->strt_content[j];
  s1->strt_length = size;
  /* invariants re-established */
}

/* Return a new string of len characters equal to the len characters of s
 * beginning at position start.  The  original string s is unchanged.
 * If start + len exceeds the actual length of the string, the
 * returned string consists of the characters from index start to the end of s.
 * Precondition: both start and len are at least 0.
 */
str_t substring(str_t s, int start, int len) {
  int i,j;
  /* We are to return a new str_t instance no matter what. */
  str_t newstr = malloc(sizeof(struct strstr));
  /* If the start position is beyond the end, just return an empty string */
  if (start >= s->strt_length) {
    newstr->strt_length = 0;
    newstr->strt_capacity = DFLTCAP;
    newstr->strt_content = malloc(DFLTCAP);
    return newstr;
  }
  /* start < s->strt_length */
  /* the substring mustn't extend beyond the end of s */
  if (len > s->strt_length - start)
    len = s->strt_length - start;
  /* start + len <= s->strt_length */

  /* now find the smallest chunksize that will hold the substring */
  int need = len + EXTRA;
  newstr->strt_capacity = DFLTCAP;
  while (newstr->strt_capacity < need)
    newstr->strt_capacity += DFLTCAP;
  newstr->strt_length = len;
  newstr->strt_content = malloc(newstr->strt_capacity);
  for (i=0, j=start; i < len; i++, j++)
    newstr->strt_content[i] = s->strt_content[j];
  return newstr;
}

void destroy(str_t s)
{
        realloc(s, 0);
}

void edit(str_t targ, str_t rpl, str_t orig)
{
        if(targ->strt_length < 1){
                // do nothing
        }
        else{
                int need = orig->strt_length - targ->strt_length + rpl->strt_length + EXTRA;
                int size = orig->strt_capacity;

                if(size < need){  /* do we need to allocate more space? */
                        do{  /* yes - figure out how much */
                                size += DFLTCAP;
                        }while(size < need);
                        /* size >= needed */
                        orig->strt_content = realloc(orig->strt_content,size);
                        orig->strt_capacity = size;
                }
                /* while the substring strt "targ" exist in orig, "targ" -> "rpl" */
                int orig_loc = 0;
                int final_loc = 0;
                str_t final = malloc(sizeof(struct strstr));
                copy(final, orig);
                str_t temp = malloc(sizeof(struct strstr));
                while(orig_loc < orig->strt_length){
                        temp = substring(orig, orig_loc, targ->strt_length);
                        if(equals(temp, targ) == 1){
                                /* replace targ with rpl at that location [loc,loc + targ's length] */
                                for(int i = 0; i < rpl->strt_length; i++){
                                        final->strt_content[final_loc + i] = rpl->strt_content[i];
                                }
                                // update final_loc
                                final_loc += rpl->strt_length;
                                orig_loc += targ->strt_length;
                        }
                        else{
                                // append that char into strt final
                                final->strt_content[final_loc] = orig->strt_content[orig_loc];
                                // go to next char
                                orig_loc++;
                                final_loc++;
                        }
                }
                destroy(temp);
                copy(orig, final);
                destroy(final);


        }
        printf("%s\n", to_chars(orig));

}
