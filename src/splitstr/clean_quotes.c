/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:51:13 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/20 08:39:03 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

int	ft_quote_cut_len(char *str)
{
	int		j;
	char	quote;
	int		cut;
	
	quote = 0;
	j = 0;
	cut = 0;
	while (str[j])
	{
		if (quote && str[j] == quote)
		{
			cut += 2;
			quote = 0;
		}
		else if (!quote && (str[j] == '\'' ||str[j] == '"'))
			quote = str[j];
		j++;
	}
	return (j - cut);
}

int	ft_clean_quotes(char **str)
{
	char		*new;
	size_t		len;
	int			i;
	int			j;
	char		quote;
	
	while (*str)
	{
		i = 0;
		j = 0;
		quote = 0;
		len = ft_quote_cut_len(*str);
		if (len != ft_strlen(*str))
		{
			new = malloc(sizeof(char) * (len + 1));
			if (!new)
				return (1);
			while ((*str)[j])
			{
				if (quote && (*str)[j] == quote)
					quote = 0;
				else if (!quote && ((*str)[j] == '\'' || (*str)[j] == '"'))
					quote = (*str)[j];
				else
					new[i++] = (*str)[j];
				j++;
			}
			new[i] = '\0';
			free (*str);
			*str = new;
			if (quote)
				return ((int)ft_error(QUOTE, NULL, 1));
		}
		str++;
	}
	return (1);
}


/* int	ft_clean_quotes(char **str)
{
	char	*new;
	int		len;
	int		i;
	int		j;
	
	i = 1;
	while (*str)
	{
		len = ft_strlen(*str);
		if (((*str)[0] == '"' && (*str)[len - 1] == '"') ||
				((*str)[0] == '\'' && (*str)[len - 1] == '\''))
		{
			new = malloc(sizeof(char) * (len - 2 + 1));
			if (!new)
				return (1);
			while (i < len - 1)
			{
				new[i - 1] = (*str)[i];
				i++;
			}
			new[i - 1] = '\0';
			free (*str);
			*str = new;
		}
		str++;
	}
	return (0);
} */