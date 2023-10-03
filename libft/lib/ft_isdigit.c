/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:53:10 by jzubizar          #+#    #+#             */
/*   Updated: 2023/04/27 18:06:32 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
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
		printf("mine: %i\n", ft_isdigit(argv[1][0]));
		printf("orig: %i\n", isdigit(argv[1][0]));
	}
	return (0);
}*/
