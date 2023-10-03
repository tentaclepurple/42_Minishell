/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:31:45 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:41:41 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	ptr = NULL;
	if (!*needle)
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (!needle[j + 1])
			{
				ptr = (char *)&haystack[i];
				return (ptr);
			}
			j++;
		}
		i++;
	}
	return (ptr);
}
/*
#include<stdio.h>
#include<string.h>

int	main(void)
{
	char	*hy;
	char	*need;

	hy = "Hola Josu que tal";
	need = "";
	printf("%s\n", ft_strnstr(hy, need, 15));
	printf("%s\n", strnstr(hy, need, 15));
}*/
