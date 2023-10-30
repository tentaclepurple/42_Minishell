/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_it.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:03:47 by imontero          #+#    #+#             */
/*   Updated: 2023/10/30 09:12:28 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/* 
saving backup positions and restoring them when needed. 
If a mismatch occurs without available wildcards, 
it returns 0 for no match. After the loop, 
it skips any remaining asterisk wildcards in the pattern. 
If the end of the pattern is reached, it's considered a match.
*/
int wc_find_match(char *pattern, char *str) 
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
            return 0;
    }
    while (pattern[pat_idx] == '*')
        pat_idx++;
    return (pattern[pat_idx] == '\0');
}

int main(void) 
{
    char *pattern = "mi*ni*";
    char *str = "minishell.c";
    if (wc_find_match(pattern, str))
        printf("Matched: %s\n", str);
    else
        printf("No match found.\n");
    return (0);
}
