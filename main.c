/* Joao Paulo Mendes de Sa */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#ifndef STRSTR_H
#define STRSTR_H
#include "strstr.h"
#endif

/* Check whether memory allocation fails. */
#define CHKMLC(x) \
    if ((x) == NULL){ \
        fprintf(stderr, "Malloc Failed\n"); \
        abort();}

/* Read notes from input. */
void music_read(FILE *input, int notesLen, char *notes)
{
    int i, c;

    for (i = 0; isgraph(c = getc(input)) || i < notesLen; ){
        switch (c){
            case 'A':
                notes[i] = 0;
                break;
            case 'B':
                notes[i] = 2;
                break;
            case 'C':
                notes[i] = 3;
                break;
            case 'D':
                notes[i] = 5;
                break;
            case 'E':
                notes[i] = 7;
                break;
            case 'F':
                notes[i] = 8;
                break;
            case 'G':
                notes[i] = 10;
                break;
            case '#':
                notes[i - 1]++;
                break;
            case 'b':
                notes[i - 1]--;
                if (notes[i - 1] == -1)
                    notes[i - 1] = 11;
                break;
        }
        if (c >= 'A' && c <= 'G')
            i++;
    }
}

/* Calculate pairwise pitch difference. */
void music_pitch_diff(int *notesLen, char *notes)
{
    int i;
    
    for (i = 0; i < *notesLen - 1; i++){
        notes[i] = notes[i + 1] - notes[i];
        if (notes[i] < 0)
            notes[i] += 12;
        notes[i] += '0';
    }
    (*notesLen)--;
    notes[*notesLen] = '\0';
}

int main(int argc, char *argv[])
{
    int needleLen, haystackLen;
    char *needle, *haystack, *ptr;
    FILE *input;
    if (argc < 3){
        fprintf(stderr, "Missing paramerter\n");
        abort();
    }
    input = fopen(argv[1], "r");

    while (1){
        if (fscanf(input, "%i %i", &haystackLen, &needleLen) != 2){
            fprintf(stderr, "Missing note length\n");
            abort();
        }

        if (needleLen == 0 || haystackLen == 0)
            break;

        CHKMLC(needle = malloc(sizeof(char) * needleLen));
        CHKMLC(haystack = malloc(sizeof(char) * haystackLen));

        music_read(input, haystackLen, haystack);
        music_read(input, needleLen, needle);

        music_pitch_diff(&haystackLen, haystack);
        music_pitch_diff(&needleLen, needle);

        switch(argv[2][0] - '0'){
            case 1: ptr = strstr_bf(haystack, needle);
                    break;
            case 2: ptr = strstr_kmp(haystack, needle);
                    break;
            case 3: ptr = strstr_bmh(haystack, needle);
                    break;
            case 4: ptr = strstr_bitap(haystack, needle);
                    break;
            default: ptr = strstr(haystack, needle);
        }

        if (ptr != NULL)
            printf("S %li\n", ptr - haystack);
        else
            printf("N\n");

        free(needle);
        free(haystack);
    }
    return EXIT_SUCCESS;
}
