/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putXmnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:36:35 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:43:02 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_xnumer_digits(unsigned int n, t_flag flags, int *aux)
{
	int	count;

	count = 1;
	if (flags.hash && !(n == 0))
	{
		*aux = 2;
	}
	while (n > 15)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

static int	ft_putchar_0xm(int dig, t_flag flags, char *nbr, unsigned int n)
{
	int	con;
	int	k;

	con = 0;
	k = 0;
	if (flags.hash && !(n == 0))
	{
		con += write(1, "0X", 2);
	}
	if (flags.precision && flags.precwidth)
		con += ft_print_width(flags.precwidth, dig, 1);
	while (k < dig)
		ft_putchar_fd(nbr[k++], 1);
	return (con + dig);
}

static void	ft_flags_adjust(t_flag *flags, int dig)
{
	if (flags->zeros)
	{
		flags->precision = 1;
		flags->precwidth = flags->width - 2 * flags->hash;
	}
	if (flags->precision && flags->precwidth < dig)
		flags->precwidth = dig;
	if (flags->precision)
		flags->width -= flags->precwidth - dig;
}

int	ft_putxmnbr_fd(unsigned int n, t_flag flags)
{
	char	nbr[11];
	int		i;
	int		dig;
	int		aux;

	aux = 0;
	dig = ft_xnumer_digits(n, flags, &aux);
	i = dig - 1;
	while (n > 15)
	{
		nbr[i] = "0123456789ABCDEF"[n % 16];
		n = n / 16;
		i--;
	}
	nbr[i] = "0123456789ABCDEF"[n % 16];
	i = 0;
	if (flags.precision && flags.precwidth == 0 && n == 0)
		return (ft_print_width(flags.width, 0, 0));
	ft_flags_adjust(&flags, dig);
	if (flags.justify == 1)
		i += ft_putchar_0xm(dig, flags, nbr, n);
	aux = ft_print_width(flags.width, dig + aux, flags.zeros);
	if (flags.justify == 0)
		i += ft_putchar_0xm(dig, flags, nbr, n);
	return (i + aux);
}
