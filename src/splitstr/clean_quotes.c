/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:51:13 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/17 12:38:22 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

int	ft_clean_quotes(char **str)
{
	char	*new;
	int		len;
	int		i;
	
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
}