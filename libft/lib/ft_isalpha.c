/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:39:37 by jzubizar          #+#    #+#             */
/*   Updated: 2023/04/17 18:51:31 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
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
		printf("mine: %i\n", ft_isalpha(argv[1][0]));
		printf("orig: %i\n", isalpha(argv[1][0]));
	}
	return (0);
}*/
