/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correc_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:39:38 by josu              #+#    #+#             */
/*   Updated: 2023/10/16 18:00:47 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

static int	ft_correc_len(char **str, char *spec)
{
	int	len;

	len = 1;
	if (!*str)
		return (0);
	while (str[0] && str[1])
	{
		if (ft_strchr(spec, str[0][0]) && (str[0][0] == str[1][0])
			&& ft_strlen(str[0]) == 1 && ft_strlen(str[1]) == 1)
		{
			str ++;
		}
		len++;
		str++;
	}
	return (len);
}	

char	*ft_fill_wrd(char *str)
{
	char	*n_wrd;

	n_wrd = malloc(3);
	if (!n_wrd)
		return (NULL);
	*n_wrd = str[0];
	*(n_wrd + 1) = str[0];
	*(n_wrd + 2) = '\0';
	return (n_wrd);
}

static int ft_correc_fill(char **res, char **str, char *spec)
{
	int		len;
	char	*n_wrd;

	len = 0;
	if (!*str)
		return (0);
	while (str[0] && str[1])
	{
		if (ft_strchr(spec, str[0][0]) && (str[0][0] == str[1][0])
			&& ft_strlen(str[0]) == 1 && ft_strlen(str[1]) == 1)
		{
			n_wrd = ft_fill_wrd(str[0]);
			if (!n_wrd)
				return (ft_free_split(str), 1);
			free(str[0]);
			free(str[1]);
			res[len++] = n_wrd;
			str ++;
		}
		else
			res[len++] = *str;
		str++;
	}
	if (str)
		res[len++] = *str;
	free(str);
	res[len] = NULL;
	return (0);
}	

char	**ft_correc_special(char **str, char *spec)
{
	int		n_len;
	char	**res;

	n_len = ft_correc_len(str, spec);
	res = malloc(sizeof(char *) * n_len + 1);
	if (!res)
		return (ft_free_split(str), NULL);
	if (ft_correc_fill(res, str, spec))
		return (ft_free_split(res), NULL);
	return (res);
}
