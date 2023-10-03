/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:29:20 by novadecordi       #+#    #+#             */
/*   Updated: 2023/08/03 11:42:10 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//Print spaces or Zeros
int	ft_print_width(int tot_width, int filled, int zeros)
{
	int	i;

	i = 0;
	while (tot_width - filled > 0)
	{
		if (zeros)
			i += write(1, "0", 1);
		else
			i += write(1, " ", 1);
		tot_width--;
	}
	return (i);
}

//initialize to 0 the t_flag variable
t_flag	ft_flags_zeros(void)
{
	t_flag	flags;

	flags.zeros = 0;
	flags.justify = 0;
	flags.precision = 0;
	flags.width = 0;
	flags.hash = 0;
	flags.space = 0;
	flags.plus = 0;
	flags.precwidth = 0;
	return (flags);
}

//Length of the digit part in the string
int	ft_adv_flag(const char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}

//Auxiliar function for ft_process_flags
static void	ft_process_flags_isdigit(t_flag *flags, const char *str, int *i)
{
	if (flags->precision)
		flags->precwidth = ft_atoi(&str[*i]);
	else
		flags->width = ft_atoi(&str[*i]);
	*i += ft_adv_flag(&str[*i]) - 1;
}

//Setting the readed flags into "flags" variable
int	ft_process_flags(int i, t_flag *flags, const char *str)
{
	while (str[i] && !ft_is_type(str[i]))
	{
		if (str[i] == '0' && flags->justify == 0 && flags->precision == 0)
			flags->zeros = 1;
		else if (ft_isdigit(str[i]))
			ft_process_flags_isdigit(flags, str, &i);
		else if (str[i] == '-')
		{
			flags->justify = 1;
			flags->zeros = 0;
		}
		else if (str[i] == '.')
		{
			flags->precision = 1;
			flags->zeros = 0;
		}
		else if (str[i] == '#')
			flags->hash = 1;
		else if (str[i] == ' ')
			flags->space = 1;
		else if (str[i] == '+')
			flags->plus = 1;
		i++;
	}
	return (i);
}
