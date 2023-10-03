/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfputnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:58:32 by novadecordi       #+#    #+#             */
/*   Updated: 2023/08/03 11:42:40 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_numer_digits(int n)
{
	int	count;

	count = 1;
	if (n == -2147483648)
		return (10);
	else if (n < 0)
		n *= -1;
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
		nbr[9] = '8';
		*n = *n / 10;
		*i -= 1;
	}
}

int	ft_precision_nul(t_flag *flags)
{
	int	i;

	i = 0;
	if (flags->plus && flags->justify)
		i += write(1, "+", 1);
	if (flags->space && flags->justify)
		i += write(1, " ", 1);
	i += ft_print_width(flags->width, flags->plus + flags->space, 0);
	if (flags->plus && !flags->justify)
		i += write(1, "+", 1);
	if (flags->space && !flags->justify)
		i += write(1, " ", 1);
	return (i);
}

int	ft_pfputnbr_fd(int n, int fd, t_flag flags)
{
	char	nbr[12];
	int		i;
	int		dig;
	int		nb;

	dig = ft_numer_digits(n);
	i = dig - 1;
	nb = n;
	nbr[i + 1] = '\0';
	ft_itoa_min(&n, nbr, &i);
	if (n < 0 && fd)
		n *= -1;
	while (n > 9 && fd)
	{
		nbr[i] = "0123456789"[n % 10];
		n = n / 10;
		i--;
	}
	nbr[i] = "0123456789"[n % 10];
	if (flags.precision && flags.precwidth == 0 && n == 0)
	{
		i = ft_precision_nul(&flags);
		return (i);
	}
	return (ft_print_nbr(nbr, flags, nb));
}
