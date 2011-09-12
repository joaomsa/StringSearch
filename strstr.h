/* Joao Paulo Mendes de Sa */

/* strstr() using brute force search. */
char *strstr_bf(char *haystack, char *needle);

/* strstr() using Knuth-Morris-Pratt algorithm. */
char *strstr_kmp(char *haystack, char *needle);

/* strstr() using Boyer-Moore-Horspool algorithm. */
char *strstr_bmh(char *haystack, char *needle);

/* strstr() using bitap (shift-or) algorithm. */
char *strstr_bitap(char *haystack, char *needle);
