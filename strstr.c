#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* strstr() using brute force search. */
char *strstr_bf(char *haystack, char *needle);

/* strstr() using Knuth-Morris-Pratt algorithm. */
char *strstr_kmp(char *haystack, char *needle)
{
    int *matchTable, pos, cnd, shift;

    matchTable = malloc(sizeof(int) * strlen(needle));
    /* Build partial match table for string needle. */
    pos = 2; /* Current postion of matchTable being computed. */
    cnd = 0; /* Last character of prefix candidate for current substring. */
    matchTable[0] = -1;
    matchTable[1] = 0;
    while (needle[pos] != '\0'){
        if (needle[pos - 1] == needle[cnd]){ /* Prefix found. */
            matchTable[pos] = cnd + 1;
            pos++; cnd++;
        } else if (cnd > 0) /* Fall back on next candidate. */
            cnd = matchTable[cnd];
        else { /* No candidates. (cnd = 0)*/
            matchTable[pos] = 0;
            pos++;
        }
    }

    /* Search for string needle in string haystack. */
    pos = 0;
    shift = 0;
    while (haystack[pos + shift] != '\0' && needle[pos] != '\0'){
        if (haystack[pos + shift] == needle[pos])
            pos++;
        else {
            shift += pos - matchTable[pos];
            if (pos > 0)
                pos = matchTable[pos];
        }
    }
    free(matchTable);

    if (needle[pos] == '\0')
        return haystack + shift;
    else /* needle not found. */
        return NULL;
}

/* strstr() using Boyer-Moore-Horspool algorithm. */
char *strstr_bmh(char *haystack, char *needle);

/* strstr() using bitap (shift-and) algorithm. */
char *strstr_bitap(char *haystack, char *needle);

int main(){
    int i, c;
    char *ptr, haystack[1000], needle[1000];
    for (i = 0; (c = getchar()) != '\n'; i++)
        haystack[i] = c;
    haystack[i] = '\0';
    for (i = 0; (c = getchar()) != '\n' && c != EOF; i++)
        needle[i] = c;
    needle[i] = '\0';
    printf("%s\n%s\n####\n", haystack, needle);

    ptr = strstr(haystack, needle);
    printf("strstr = ");
    if (ptr == NULL)
        printf("NULL\n");
    else
        printf("%lu\n", ptr - haystack);

    ptr = strstr_kmp(haystack, needle);
    printf("strstr_kmp = ");
    if (ptr == NULL)
        printf("NULL\n");
    else
        printf("%lu\n", ptr - haystack);
    return 0;
}
