#include <stdio.h>

int custom_fnmatch(const char *pattern, const char *str) 
{
    while (*pattern)
	{
        if (*pattern == '*') {
            while (*pattern == '*')
                pattern++;
            if (*pattern == '\0')
                return 1;
            while (*str)
			{
                if (*str == *pattern && custom_fnmatch(pattern, str))
                    return 1;
                str++;
            }
            return 0;
        }
        if (*str == '\0' || (*pattern != *str))
            return 0;
        pattern++;
        str++;
    }
    return (*str == '\0');
}

int main() {
    const char *pattern = "mi*.*";
    const char *str = "minishell.c";
    if (custom_fnmatch(pattern, str)) {
        printf("Matched: %s\n", str);
    } else {
        printf("No match found.\n");
    }
    return 0;
}
