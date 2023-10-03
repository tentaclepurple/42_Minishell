/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:13:56 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:41:38 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1[i] != s2[i] && i != n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
/*
#include<stdio.h>
#include<string.h>

int	main(void)
{
	char *s1 = "\200";
    char *s2 = "\0";

	printf("%i\n", ft_strncmp(s1, s2, strlen(s1)));
	printf("%i\n", strncmp(s1, s2, strlen(s1)));
	
	return (0);
}*/
