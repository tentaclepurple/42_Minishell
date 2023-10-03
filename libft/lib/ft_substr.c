/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:27:23 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:41:51 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	int		deflen;
	int		i;

	i = 0;
	if (ft_strlen(s) < start)
		deflen = 0;
	else if (ft_strlen(&s[start]) > len)
		deflen = len;
	else
		deflen = ft_strlen(&s[start]);
	substr = malloc(sizeof(char) * (deflen + 1));
	if (substr == NULL)
		return (NULL);
	while (i < deflen)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/*
#include<stdio.h>
#include<string.h>

int	main(void)
{
	char	*hy;
	char	*res;

	hy = "Hola Josu que tal";
	res = ft_substr(hy, 3, 20);
	printf("%s\n", res);
	free (res);
	return (0);
}*/
