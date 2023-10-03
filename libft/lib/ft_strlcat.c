/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:25:40 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:41:26 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(dst);
	if (len >= dstsize)
		return (ft_strlen(src) + dstsize);
	if (dstsize > 0)
	{
		while (i < dstsize - 1 - len && src[i])
		{
			dst[len + i] = src[i];
			i++;
		}
		dst[len + i] = '\0';
	}
	while (src[i])
		i++;
	if (!dstsize)
		return (i);
	return (len + i);
}
/*
#include<stdio.h>
#include<string.h>

int	main(void)
{
	char	*dst;
	char	*src;
	char	*ex;
	size_t	i;

	dst = malloc(50);
	src = "abc";
	ex = "0123456";
	dst[0] = 'A';
	dst[1] = 'A';
	dst[2] = 'A';
	dst[3] = '\0';
	i = ft_strlcat(dst, src, 6);
	printf("i: %i\n", (int)i);
	printf("d: %s\n", dst);
	free (dst);
	dst = malloc(50);
	dst[0] = 'A';
	dst[1] = 'A';
	dst[2] = 'A';
	dst[3] = '\0';
	i = strlcat(dst, src, 3);
	printf("i: %i\n", (int)strlcat(dst, "abc", 6));
	printf("d: %s\n", dst);
	free (dst);
}*/
