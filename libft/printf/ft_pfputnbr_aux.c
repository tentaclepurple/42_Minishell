/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfputnbr_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:58:32 by novadecordi       #+#    #+#             */
/*   Updated: 2023/08/03 11:42:37 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_putsign(int n, t_flag *flags)
{
	int	i;

	i = 0;
	if (n < 0)
		i += write(1, "-", 1);
	else if (flags->plus)
		i += write(1, "+", 1);
	else if (flags->space)
	{
		i += write(1, " ", 1);
		flags->space = 0;
		flags->width--;
	}
	return (i);
}

static int	ft_print_number(char *nbr, int n, t_flag flags)
{
	int	i;

	i = 0;
	if (flags.zeros == 0)
	{
		if (n < 0)
			i += write(1, "-", 1);
		else if (flags.plus)
			i += write(1, "+", 1);
		else if (flags.space)
			i += write(1, " ", 1);
	}
	if (flags.precision && flags.precwidth)
		i += ft_print_width(flags.precwidth, ft_strlen(nbr), 1);
	i += ft_pfputstr_fd(nbr, 1);
	return (i);
}

//Auxiliar function for ft_print_nbr
static void	ft_print_nbr_aux(t_flag *flags, int *i, char *nbr, int n)
{
	if (flags->zeros)
		*i += ft_putsign(n, flags);
	if (flags->justify)
		*i += ft_print_number(nbr, n, *flags);
	if (flags->precision && (size_t)flags->precwidth < ft_strlen(nbr))
		flags->precwidth = ft_strlen(nbr);
}

int	ft_print_nbr(char *nbr, t_flag flags, int n)
{
	int	i;
	int	sign;

	sign = 0;
	if (n < 0)
	{
		sign = 1;
		flags.plus = 0;
		flags.space = 0;
	}
	i = 0;
	ft_print_nbr_aux(&flags, &i, nbr, n);
	if (flags.precision)
	{
		flags.width -= flags.precwidth;
		if (n < 0 || flags.plus || flags.space)
			flags.width -= 1;
		i += ft_print_width(flags.width, 0, 0);
	}
	else
		i += ft_print_width(flags.width - flags.plus - flags.space,
				ft_strlen(nbr) + sign, flags.zeros);
	if (flags.justify == 0)
		i += ft_print_number(nbr, n, flags);
	return (i);
}
