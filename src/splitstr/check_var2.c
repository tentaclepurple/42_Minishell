/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:43:53 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/02 09:46:37 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse.h"

size_t	ft_strlen_var(const char *s, int quote)
{
	size_t	i;
	char	ch[2];

	i = 0;
	if (quote)
	{
		ch[0] = '"';
		ch[1] = '\'';
	}
	else
	{
		ch[0] = ' ';
		ch[1] = ' ';
	}
	while (s[i] && s[i] != ' ' && (s[i] != ch[0] && s[i] != ch[1]))
	{
		i++;
	}
	return (i);
}

int	ft_len_var_cond(char *env, char *str, int index, int quote)
{
	int		len_var;
	char	*ito_gstat;

	if (env)
		len_var = ft_strlen(&env[ft_strlen_var(&str[index + 1], quote)]);
	else if (str[index + 1] == '?')
	{
		ito_gstat = ft_itoa(g_stat);
		len_var = ft_strlen(ito_gstat);
		free(ito_gstat);
	}
	else
		len_var = 0;
	return (len_var);
}

char	*ft_expand_concat(char *env, int len, char *res, char ch)
{
	char	*ito_gstat;

	if (env)
	{
		while (*env != '=')
			env++;
		env++;
		ft_strlcat(res, env, len + 2);
	}
	else if (ch == '?')
	{
		ito_gstat = ft_itoa(g_stat);
		ft_strlcat(res, ito_gstat, len + 2);
		free(ito_gstat);
	}
	return (res);
}
