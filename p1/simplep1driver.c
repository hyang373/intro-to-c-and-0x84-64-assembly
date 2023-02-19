#include <stdio.h>
#include "p1.h"

/* NOTE: This code is a quick-and-dirty test driver.
 * It is NOT an example of good code hygiene, because of the many naked
 * constants and cryptic outputs.  But it should be helpful in debugging.
 */
int main() {
  int retval, i;
  str_t shortstr = create("a short string");
  str_t alpha = create("abcdefghijkl");
  str_t beta = create("b");
  str_t empty = create("");
  str_t bad = create("bad");
  str_t s = create("nothing");
  str_t last;

  retval = length(shortstr);
  if (retval != 14)
    printf("Fail: wrong length on shortstr: %d.\n",retval);
  else
    printf("1");
  retval = length(alpha);
  if (retval != 12)
    printf("Fail: wrong length on alpha: %d\n",retval);
  else
    printf("..2");
  retval = length(beta);
  if (retval != 1)
    printf("Fail: wrong length on beta: %d\n",retval);
  else
    printf("..3");
  retval = length(empty);
  if (retval != 0)
    printf("Fail: wrong length on s: %d\n",retval);
  else
    printf("..4");
  copy(s,shortstr);
  if (!equals(s,shortstr))
    printf("Fail: shortstr != s after copy.\n");
  else
    printf("..5");

  /* censor() and to_chars() */
  censor(alpha,bad);
  printf("\ncensor output (should be [  c efghijkl]): [%s]\n",
         to_chars(alpha));

  /* append and substring */
  copy(s,bad);

  for (i=0; i<5; i++)
    append(s,alpha);
  retval = length(s);
  if (retval != 63) {
    printf("Fail: wrong length after append(s,alpha) five times: %d\n",retval);
    printf("Actual value of s is %s\n",to_chars(s));
  } else
    printf("...6\n");

  last = substring(s,27,12);
  if (!equals(last,alpha))
    printf("Fail: incorrect substring of s: expected %s, got %s.\n",
           to_chars(alpha),to_chars(last));
  else
    printf("...7.\n");
  return 0;
}
