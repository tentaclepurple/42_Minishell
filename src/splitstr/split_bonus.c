/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:14:34 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/15 09:17:19 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsebonus.h"

/* Sub function for ft_split_str */
static int	ft_split_low(char **split, char const *s, char c)
{
	char	*str;
	char	*word;
	int		len;
	int		i;

	str = (char *)s;
	i = 0;
	while (i < ft_nbr_wrd(s, c))
	{
		len = ft_str_chlen(str, c);
		if (len > 0)
		{
			word = malloc(sizeof(char) * (len + 1));
			if (word == NULL)
				return (i + 1);
			word = ft_fill_word(word, str, len);
			split[i] = word;
			str += len + 1;
			i++;
		}
		else
			str++;
	}
	split[ft_nbr_wrd(s, c)] = NULL;
	return (0);
}

//Splits a String into a 2D string array, taking quotes into account"
char	**ft_split_str(char const *s, char c)
{
	char	**split;
	int		err;
	int		i;

	if (!ft_nbr_wrd(s, c))
		return (NULL);
	split = malloc(sizeof(char *) * (ft_nbr_wrd(s, c) + 1));
	if (split == NULL)
		return (ft_error(MEM, NULL, 2));
	err = ft_split_low(split, s, c);
	if (err)
	{
		i = 0;
		while (i < err - 1)
		{
			free(split[i]);
			i++;
		}
		free (split);
		return (ft_error(MEM, NULL, 2));
	}
	return (split);
}

//Returns the length of the corrected string fot ft_correct_str
int	ft_strcorr_len(char	*str, char *act)
{
	unsigned int	i;
	int				extra;

	i = 0;
	extra = 0;
	while (str[i])
	{
		ft_mv_in_quotes(str, &i);
		if (ft_strchr(act, str[i]))
			extra += 2;
		if (str[i])
			i++;
	}
	return (i + extra);
}

//Auxiliar function of correct string, with the conditional statements
void	ft_aux_correct_str(char *res, char *str, int *i, int *extra)
{
	char	quote;

	if (str[*i] == '\"' || str[*i] == '\'')
	{
		quote = str[*i];
		res[*i + *extra] = str[*i];
		(*i)++;
		while (str[*i])
		{
			res[*i + *extra] = str[*i];
			if (str[*i] == quote)
				break ;
			(*i)++;
		}
	}
	if (ft_strchr("<>|&()", str[*i]))
	{
		res[*i + *extra] = ' ';
		res[*i + *extra + 1] = str[*i];
		res[*i + *extra + 2] = ' ';
		(*extra) += 2;
	}
	else
		res[*i + *extra] = str[*i];
}

//Adds spaces into the string, separating the special characters
// str is freed in terminal function
char	*ft_correct_str(char *str)
{
	char	*res;
	int		i;
	int		extra;

	i = 0;
	extra = 0;
	res = malloc(ft_strcorr_len(str, "<>|&()") + 1);
	if (!res)
		return (ft_error(MEM, NULL, 2));
	while (str[i])
	{
		ft_aux_correct_str(res, str, &i, &extra);
		if (str[i])
			i++;
	}
	res[i + extra] = '\0';
	return (res);
}
