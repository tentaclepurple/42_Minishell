/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:36:35 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:42:59 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_unumer_digits(unsigned int n)
{
	int	count;

	count = 1;
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static int	ft_putusign(t_flag *flags)
{
	int	i;

	i = 0;
	if (flags->plus)
		i += write(1, "+", 1);
	else if (flags->space)
	{
		i += write(1, " ", 1);
		flags->space = 0;
		flags->width--;
	}
	return (i);
}

static int	ft_print_unumber(char *nbr, t_flag flags)
{
	int	i;

	i = 0;
	if (flags.zeros == 0)
	{
		if (flags.plus)
			i += write(1, "+", 1);
		else if (flags.space)
			i += write(1, " ", 1);
	}
	if (flags.precision && flags.precwidth)
		i += ft_print_width(flags.precwidth, ft_strlen(nbr), 1);
	i += ft_pfputstr_fd(nbr, 1);
	return (i);
}

static int	ft_print_unbr(char *nbr, t_flag flags, unsigned int n)
{
	int	i;

	i = 0;
	if (flags.zeros)
		i += ft_putusign(&flags);
	if (flags.justify)
		i += ft_print_unumber(nbr, flags);
	if (flags.precision && (size_t)flags.precwidth < ft_strlen(nbr))
		flags.precwidth = ft_strlen(nbr);
	if (flags.precision)
	{
		flags.width -= flags.precwidth;
		if (n < 0 || flags.plus || flags.space)
			flags.width -= 1;
		i += ft_print_width(flags.width, 0, 0);
	}
	else
		i += ft_print_width(flags.width - flags.plus - flags.space,
				ft_strlen(nbr), flags.zeros);
	if (flags.justify == 0)
		i += ft_print_unumber(nbr, flags);
	return (i);
}

int	ft_putunbr_fd(unsigned int n, int fd, t_flag flags)
{
	char			nbr[12];
	int				i;
	int				dig;
	unsigned int	nb;

	dig = ft_unumer_digits(n);
	i = dig - 1;
	nb = n;
	nbr[i + 1] = '\0';
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
	return (ft_print_unbr(nbr, flags, nb));
}
