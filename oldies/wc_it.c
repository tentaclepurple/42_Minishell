#include <stdio.h>

/* 
saving backup positions and restoring them when needed. 
If a mismatch occurs without available wildcards, 
it returns 0 for no match. After the loop, 
it skips any remaining asterisk wildcards in the pattern. 
If the end of the pattern is reached, it's considered a match.
*/
int custom_fnmatch(char *pattern, char *str) 
{
    int str_idx = 0;
    int pat_idx = 0;
    int str_b = -1;
    int pat_b = -1;

    while (str[str_idx])
	{
        if (pattern[pat_idx] == '*') 
		{
            pat_b = ++pat_idx;
            str_b = str_idx;
        }
		else if (pattern[pat_idx] == str[str_idx]) 
		{
            pat_idx++;
            str_idx++;
        }
		else if (pat_b >= 0) 
		{
            pat_idx = pat_b;
            str_idx = ++str_b;
        }
		else
            return 0; // No hay coincidencia
    }
    while (pattern[pat_idx] == '*')
        pat_idx++; // Saltar comodines restantes
    return (pattern[pat_idx] == '\0');
}

int main() {
    char *pattern = "mi*ni*";
    char *str = "minishell.c";
    if (custom_fnmatch(pattern, str)) {
        printf("Matched: %s\n", str);
    } else {
        printf("No match found.\n");
    }
    return 0;
}
