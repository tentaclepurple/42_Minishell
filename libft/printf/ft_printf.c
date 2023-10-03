/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 10:25:55 by novadecordi       #+#    #+#             */
/*   Updated: 2023/08/03 11:42:48 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_nbr_args(const char *str)
{
	unsigned int	i;
	int				nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == '%')
		{
			nbr++;
			i++;
		}
		else if (str[i] == '%')
			nbr++;
		i++;
	}
	return (nbr);
}

static int	ft_len_arg_def(const char *str, char *type, t_flag *flags)
{
	unsigned int	i;

	i = 0;
	if (str[i])
		i++;
	i = ft_process_flags(i, flags, str);
	*type = ft_is_type(str[i]);
	if (str[i])
		i++;
	return (i);
}

static void	ft_put_arg(va_list *value, char type, int *cont, t_flag flags)
{
	if (type == 'c')
		*cont += ft_print_char_fd(va_arg(*value, int), flags, 1);
	else if (type == 's')
		*cont += ft_pfputargstr_fd(va_arg(*value, const char *), 1, flags);
	else if (type == 'u')
		*cont += ft_putunbr_fd(va_arg(*value, unsigned int), 1, flags);
	else if (type == 'x')
		*cont += ft_putxnbr_fd(va_arg(*value, unsigned int), flags);
	else if (type == 'X')
		*cont += ft_putxmnbr_fd(va_arg(*value, unsigned int), flags);
	else if (type == 'p')
		*cont += ft_putxptr_fd(va_arg(*value, void *), 1, flags);
	else if (type == 'i' || type == 'd')
		*cont += ft_pfputnbr_fd(va_arg(*value, int), 1, flags);
	else if (type == '%')
		*cont += ft_print_char_fd('%', flags, 1);
}

// Variadic function to add numbers
int	ft_printf(const char *str, ...)
{
	int		n;
	va_list	ptr;
	char	type;
	int		cont;
	t_flag	flags;

	cont = 0;
	flags = ft_flags_zeros();
	n = ft_nbr_args(str);
	type = 0;
	va_start(ptr, str);
	cont += ft_pfputstr_fd(str, 1);
	str += ft_pfstrlen(str);
	str += ft_len_arg_def(str, &type, &flags);
	while (n >= 0)
	{
		ft_put_arg(&ptr, type, &cont, flags);
		cont += ft_pfputstr_fd(str, 1);
		str += ft_pfstrlen(str);
		flags = ft_flags_zeros();
		str += ft_len_arg_def(str, &type, &flags);
		n--;
	}
	va_end(ptr);
	return (cont);
}
