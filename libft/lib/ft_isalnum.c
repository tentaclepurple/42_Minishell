/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:57:43 by jzubizar          #+#    #+#             */
/*   Updated: 2023/04/27 18:06:14 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
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
		printf("mine: %i\n", ft_isalnum(argv[1][0]));
		printf("orig: %i\n", isalnum(argv[1][0]));
	}
	return (0);
}*/
