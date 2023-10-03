/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:03:09 by jzubizar          #+#    #+#             */
/*   Updated: 2023/04/17 19:05:49 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
#include<ctype.h>
#include<stdio.h>
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("mine: %i\n", ft_isascii(argv[1][0]));
		printf("orig: %i\n", isascii(argv[1][0]));
	}
	return (0);
}*/