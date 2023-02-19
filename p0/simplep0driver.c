#include <stdio.h>
#include "p0.h"   /* use quotes for local (non-system) header files */

#define STRBUFLEN 12

int main() {
  char base[STRBUFLEN];
  char suf[STRBUFLEN] = {' ', '2', '7', '0', 0 };
  char *test = "test";
  char *bad = "hello";

  printf("str_length(test) returns %d.\n",str_length(test));
  printf("str_isalpha(suf) returns %d.\n",str_isalpha(suf));
  printf("str_length(\"this is a test\") returns %d.\n",
         str_length("this is a test"));
  printf("str_isalpha(bad) returns %d.\n",str_isalpha(bad));
  str_copy(base,test);
  printf("after str_copy, base is %s.\n",base);
  str_concat(base,suf);
  printf("after str_concat, base is %s.\n",base);
  str_censor(base,bad);
  printf("after str_censor, base is %s.\n",base);
  return 0;
}
