#include "p0.h"

#define ASCII_A 65
#define ASCII_Z 90
#define ASCII_a 97
#define ASCII_z 122

/* returns the number of characters in the sequence pointed to
 * by first arg, excluding the null terminator.  I.e.,
 * does the same thing as the library function strlen().
 */
int str_length(char *s) {
        // pointer variable
        char *ptr = s;
        // a variable to keep track of length of string
        int counter = 0;

        // go through array and count the length of string/ array of chars
        while( *ptr != '\0'){
                counter++;
                ptr++;
        }

        return counter;

}

/* returns true (nonzero) iff every character in the sequence
 * pointed to by sp is a letter of the alphabet (i.e., either
 * in the range ‘a’ through ‘z’ or ‘A’ through ‘Z’).
 */
int str_isalpha(char *s) {
        char *ptr = s;
        int true = 1;
        int false = 0;

        /*
         * go through array of char and check if character is in the range ‘a’ through ‘z’ or ‘A’ through ‘Z’)
         * */
        while(*ptr != '\0'){
                if(((*ptr >= ASCII_A) && (*ptr <= ASCII_Z)) || ((*ptr >= ASCII_a) && (*ptr <= ASCII_z))){
                        // do nothing
                }
                else{
                        return false;
                }
                ptr++;
        }
        // by the end, if all character are alphabets, return true (1)
        return true;
}

/* copies the contents of the character sequence indicated by from
 * (including the null terminator) into the space indicated by to.
 */
void str_copy(char *to, char *from) {
        char *ptr = from;
        int counter = 0;
        // copy everything before the null terminator
        while (*ptr != '\0'){
                to[counter] = *ptr;
                ptr++;
                counter++;
        }
        // copy the null terminator
        to[counter] = '\0';
}

/* modifies the string pointed to by sp by replacing each character
 * that is in the sequence “bad” with a space character ’ ’.
 */
void str_censor(char *sp, char *bad) {
        // pointer pointed to beginning of sp
        char *ptr = sp;
        // length of the sequence "bad"
        int len_bad = str_length(bad);

        int i;
        while(*ptr != '\0'){
                for(i = 0; i < len_bad; i++){
                        // if character in sp is also in bad, replace with a space
                        if(*ptr == bad[i]){
                                *ptr = ' ';
                        }
                }
                // go to next character
                ptr++;
        }



}

/* appends the string pointed to by suffix to the string pointed to by base */
void str_concat(char *base, char *suffix) {
        char *ptr = base;
        int len_suffix = str_length(suffix);
        int i;
        // go to end of base array
        while(*ptr != '\0'){
                ptr++;
        }
        // add in suffix to end of base
        for(i = 0; i < len_suffix; i++){
                *ptr = suffix[i];
                ptr++;
        }
}
