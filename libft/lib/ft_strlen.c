/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:11:59 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:41:33 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
#include<stdio.h>
#include<string.h>

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("mine: %lu\n", ft_strlen(argv[1]));
		printf("orig: %lu\n", strlen(argv[1]));
	}
	return (0);
}*/
