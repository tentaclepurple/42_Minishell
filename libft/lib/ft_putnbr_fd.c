/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:36:35 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:41:04 by jzubizar         ###   ########.fr       */
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

static void	ft_itoa_min(int *n, char *nbr, int *i)
{
	if (*n == -2147483648)
	{
		nbr[0] = '-';
		nbr[10] = '8';
		*n = *n / 10;
		*i -= 1;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	nbr[11];
	int		i;
	int		dig;

	dig = ft_numer_digits(n);
	i = dig - 1;
	ft_itoa_min(&n, nbr, &i);
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
	i = 0;
	while (i < dig)
	{
		ft_putchar_fd(nbr[i], fd);
		i++;
	}
}
/*
#include<stdio.h>

int	main(void)
{
	int		nbr;

	nbr = -2147483648;
	ft_putnbr_fd(nbr, 1);
	return (0);
}*/
