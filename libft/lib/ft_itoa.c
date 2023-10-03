/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:38:34 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:40:07 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

static int	ft_numer_digits(int n)
{
	int	count;

	count = 1;
	if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_itoa_min(int *n, char *nbr, int *i)
{
	*i = ft_numer_digits(*n) - 1;
	if (*n == -2147483648)
	{
		nbr[0] = '-';
		nbr[10] = '8';
		*n = *n / 10;
		*i -= 1;
	}
	return (nbr);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		i;
	int		dig;

	dig = ft_numer_digits(n);
	nbr = malloc(sizeof(char) * (dig + 1));
	if (nbr == NULL)
		return (NULL);
	nbr = ft_itoa_min(&n, nbr, &i);
	if (nbr == NULL)
		return (NULL);
	if (n < 0)
	{
		nbr[0] = '-';
		n *= -1;
	}
	while (n > 9)
	{
		nbr[i] = "0123456789"[n % 10];
		n = n / 10;
		i--;
	}
	nbr[i] = "0123456789"[n % 10];
	nbr[dig] = '\0';
	return (nbr);
}
/*
#include<stdio.h>

int	main(void)
{
	int		nbr;
	char	*str;

	nbr = -9;
	str = ft_itoa(nbr);
	printf("%s\n", str);
	free (str);
	return (0);
}*/
