/* mylib.c */

#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include <assert.h>
#include <ctype.h>

/*****************************************************************************
 * Function: print_info
 * Input   : int freq char *word
 * Output  : void 
 * Procedure: Prints out the freq, and the word
 *****************************************************************************/

void print_info(int freq, char *word){
    printf("%-4d %s\n", freq, word);
}

/*****************************************************************************
 * Function: *emmalloc
 * Input   : size_t s
 * Output  : void 
 * Procedure: Attempts to allocate memory and exits if it fails
 *****************************************************************************/

void *emalloc(size_t s){
    void *result = malloc(s);
    if( NULL == result) {
        fprintf(stderr, "Memory allocation failed! \n");
        exit(EXIT_FAILURE);
    }
    return result;

}

/*****************************************************************************
 * Function: *erealloc
 * Input   : void *p size_t s
 * Output  : void 
 * Procedure: Attempts to allocate memory and exits if it fails
 *****************************************************************************/

void *erealloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if(NULL == result) {
        fprintf(stderr, "Memory allocation failed! \n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/*****************************************************************************
 * Function: getword
 * Input   : char *s, int limit, FILE *stream
 * Output  : int
 * Procedure: Takes in a str and the size, while its not alphanumeric grab each
              char, if its alnum add it to a char array, determine if its
              the terminating null return char array with terminating null
*****************************************************************************/

int getword(char *s, int limit, FILE *stream){
    int c;
    char *w = s;
    assert(limit > 0 && s !=NULL && stream !=NULL);

    /* skip to the start of the word */
    while(!isalnum(c = getc(stream)) && EOF != c);

    if (EOF == c) {
        return EOF;
    } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
        *w++ = tolower(c);
    }
    while (--limit > 0) {
        if(isalnum(c = getc(stream))) {
            *w++ = tolower(c);
        } else if ('\'' == c) {
            limit++;
        } else {
            break;
        }
    }
    *w = '\0';
    return w - s;
}
