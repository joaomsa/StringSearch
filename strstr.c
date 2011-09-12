/* Joao Paulo Mendes de Sa */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#ifndef STRSTR_H
#define STRSTR_H
#include "strstr.h"
#endif

/* Check whether memory allocation fails. */
#define CHKMLC(x) \
    if ((x) == NULL){ \
        fprintf(stderr, "Malloc Failed\n"); \
        abort();}

char *strstr_bf(char *haystack, char *needle)
{
    int pos, shift;

    /* Sanity check. */
    if (needle[0] == '\0')
        return haystack;

    for (shift = 0; haystack[shift] != '\0'; shift++)
        for (pos = 0; haystack[pos + shift] == needle[pos]; pos++)
            if (needle[pos + 1] == '\0')
                return haystack + shift;

    return NULL;
}

char *strstr_kmp(char *haystack, char *needle)
{
    int *matchTable, pos, cnd, shift;

    /* Sanity check. */
    if (needle[0] == '\0')
        return haystack;
    if (haystack[0] == '\0')
        return NULL;

    CHKMLC(matchTable = malloc(sizeof(int) * strlen(needle)));
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

char *strstr_bmh(char *haystack, char *needle)
{
    int needleLen, haystackLen, bcTable[UCHAR_MAX + 1], i;

    needleLen = strlen(needle);
    haystackLen = strlen(haystack);

    /* Sanity check. */
    if (needle[0] == '\0')
        return haystack;

    /* Initialize bad char shift table and populate with analysis of needle. */
    for (i = 0; i < UCHAR_MAX + 1; i++)
        bcTable[i] = needleLen;
    for (i = 0; i < needleLen - 1; i++) 
        bcTable[(unsigned char)needle[i]] = needleLen - 1 - i;

    while (haystackLen >= needleLen){
        /* Match needle to haystack from right to left. */
        for (i = needleLen - 1; needle[i] == haystack[i]; i--)
            if (i == 0)
                return haystack;

        /* Shift haystack based on bad char shift table. */ 
        haystackLen -= bcTable[(unsigned char)haystack[needleLen - 1]];
        haystack += bcTable[(unsigned char)haystack[needleLen - 1]];
    }

    /* No match. */
    return NULL;
}

char *strstr_bitap(char *haystack, char *needle)
{
    unsigned long long bitArr;
    unsigned long long needleMask[UCHAR_MAX + 1];
    int needleLen = strlen(needle), i;

    /* Sanity check. */
    if (needle[0] == '\0')
        return haystack;

    /* Pattern too long. */
    if (needleLen > 63)
        return strstr_bmh(haystack, needle);

    /* Initialize to 1111...0 */
    bitArr = ~1;

    /* Initialize the needle bitmasks. */
    for (i = 0; i < UCHAR_MAX + 1; i++)
        needleMask[i] = ~0;
    for (i = 0; i < needleLen; ++i)
        needleMask[(unsigned char)needle[i]] &= ~(1UL << i);

    for (i = 0; haystack[i] != '\0'; i++){
        /* Update bit array. */
        bitArr |= needleMask[(unsigned char)haystack[i]];
        bitArr <<= 1;

        /* If 0 reached end of bitArr then needle found. */
        if (0 == (bitArr & (1UL << needleLen)))
            return haystack + i - needleLen + 1;
    }

    return NULL;
}
