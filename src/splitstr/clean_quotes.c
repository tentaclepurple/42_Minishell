/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:51:13 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/02 12:16:24 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse.h"

//Function to calc the new length of the string once quote-cleaned
int	ft_quote_cut_len(char *str, char *quote)
{
	int		j;
	int		cut;

	*quote = 0;
	j = 0;
	cut = 0;
	while (str[j])
	{
		if (*quote && str[j] == *quote)
		{
			cut += 2;
			*quote = 0;
		}
		else if (!*quote && (str[j] == '\'' || str[j] == '"'))
			*quote = str[j];
		j++;
	}
	return (j - cut);
}

static char	*ft_new_quote(int len, char **str, char *quote)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (ft_error(MEM, NULL, 2));
	while ((*str)[j])
	{
		if (*quote && (*str)[j] == *quote)
			*quote = 0;
		else if (!(*quote) && ((*str)[j] == '\'' || (*str)[j] == '"'))
			*quote = (*str)[j];
		else
			new[i++] = (*str)[j];
		j++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_clean_quotes(char **str)
{
	char		*new;
	size_t		len;
	char		quote;

	while (*str)
	{
		quote = 0;
		len = ft_quote_cut_len(*str, &quote);
		if (len != ft_strlen(*str))
		{
			quote = 0;
			new = ft_new_quote(len, str, &quote);
			if (!new)
				return (1);
			free (*str);
			*str = new;
		}
		if (quote)
			return (ft_error(QUOTE, NULL, 1), 0);
		str++;
	}
	return (1);
}
