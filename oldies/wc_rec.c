/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_rec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:13:29 by imontero          #+#    #+#             */
/*   Updated: 2023/10/30 17:02:18 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int find_wild_match(char *pattern, char *str) 
{
    while (*pattern)
	{
        if (*pattern == '*')
        {
            while (*pattern == '*')
                pattern++;
            if (*pattern == '\0')
                return (1);
            while (*str)
			{
                if (*str == *pattern && find_wild_match(pattern, str))
                    return (1);
                str++;
            }
            return 0;
        }
        if (*str == '\0' || (*pattern != *str))
            return (0);
        pattern++;
        str++;
    }
    return (*str == '\0');
}

int main() {
    const char *pattern = "*.c";
    const char *str = "minishell.c";
    if (find_wild_match(pattern, str)) {
        printf("Matched: %s\n", str);
    } else {
        printf("No match found.\n");
    }
    return 0;
}
