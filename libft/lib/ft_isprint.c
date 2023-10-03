/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:06:09 by jzubizar          #+#    #+#             */
/*   Updated: 2023/04/27 18:06:38 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
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
		printf("mine: %i\n", ft_isprint(argv[1][0]));
		printf("orig: %i\n", isprint(argv[1][0]));
	}
	return (0);
}*/
