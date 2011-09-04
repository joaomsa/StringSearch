#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void music_read(int notesLen, char *notes)
{
    int i, c;

    for (i = 0; isgraph(c = getchar()) || i < notesLen; ){
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

int main()
{
    int needleLen, haystackLen;
    char *needle, *haystack;

    while (1){
        scanf("%i %i", &haystackLen, &needleLen);

        if (needleLen == 0 || haystackLen == 0)
            break;

        needle = malloc(sizeof(char) * needleLen);
        haystack = malloc(sizeof(char) * haystackLen);

        music_read(haystackLen, haystack);
        music_read(needleLen, needle);

#ifdef DEBUG
        int i;
        for (i = 0; i < haystackLen; i++)
            printf("%i ", haystack[i]);
        puts("");

        for (i = 0; i < needleLen; i++)
            printf("%i ", needle[i]);
        puts("");
        puts("Diff");
#endif

        music_pitch_diff(&haystackLen, haystack);
        music_pitch_diff(&needleLen, needle);

#ifdef DEBUG
        for (i = 0; i < haystackLen; i++)
            printf("%c ", haystack[i]);
        puts("");

        for (i = 0; i < needleLen; i++)
            printf("%c ", needle[i]);
        puts("");
#endif

        char *ptr;
        ptr = strstr(haystack, needle);
        if (ptr != NULL)
#ifdef DEBUG
            printf("S %li\n", ptr - haystack);
#endif
            printf("S\n");
        else
            printf("N\n");

        free(needle);
        free(haystack);
    }
    return 0;
}
