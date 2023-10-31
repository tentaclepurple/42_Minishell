/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:52:28 by imontero          #+#    #+#             */
/*   Updated: 2023/10/31 11:55:20 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse.h"

//Function to advnce the index i from quote to quote
void	ft_mv_in_quotes(char const *s, unsigned int *i)
{
	char			quote;

	if (s[*i] == '\"' || s[*i] == '\'')
	{
		quote = s[*i];
		(*i)++;
		while (s[*i])
		{
			if (s[*i] == quote)
				break ;
			(*i)++;
		}
	}
}

//Returns the number of different words you have in s
int	ft_nbr_wrd(char const *s, char c)
{
	unsigned int	i;
	unsigned int	flag;
	int				num;

	i = 0;
	flag = 0;
	num = 0;
	while (s[i])
	{
		ft_mv_in_quotes(s, &i);
		if (s[i] != c)
			flag = 1;
		else if (flag && s[i] == c)
		{
			num++;
			flag = 0;
		}
		i++;
	}
	if (flag)
		num++;
	return (num);
}

//Returns the length of the next word ins
int	ft_str_chlen(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != c && s[i])
	{
		ft_mv_in_quotes(s, &i);
		i++;
	}
	return (i);
}

//Fills the wrd string with str and a specific length
char	*ft_fill_word(char *wrd, char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		wrd[i] = str[i];
		i++;
	}
	wrd[i] = '\0';
	return (wrd);
}
