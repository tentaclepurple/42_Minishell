/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:43:53 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/11 13:37:22 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

size_t	ft_strlen_var(const char *s, int quote)
{
	size_t	i;
	char	ch;

	i = 0;
	if (quote)
		ch = '"';
	else
		ch = ' ';
	while (s[i] && s[i] != ' ' && s[i] != ch)
		i++;
	return (i);
}

char	*ft_fill_expand(char *env, char *str, int index, int quote)
{
	int		len_var;
	int		len_post;
	char	*res;
	int		i;

	i = 0;
	len_var = ft_strlen(&env[ft_strlen_var(&str[index + 1], quote)]);
	len_post = ft_strlen(&str[index + 1
			+ ft_strlen_var(&str[index + 1], quote)]);
	res = malloc(len_var + len_post + index + 2);
	if (!res)
		return (NULL);
	while (str[i] != '$')
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = '\0';
	while (*env != '=')
		env++;
	env++;
	ft_strlcat(res, env, len_var + len_post + index + 2);
	ft_strlcat(res, &str[index + 1 + ft_strlen_var(&str[index + 1], quote)],
		len_var + len_post + index + 2);
	return (res);
}

//Search the env var and changes de string
char	*ft_expand_var(char **envp, char *str, int index, int quote)
{
	int		i;
	char	*res;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], &str[index + 1],
				ft_strlen_var(&str[index + 1], quote))
			&& envp[i][ft_strlen_var(&str[index + 1], quote)] == '=')
		{
			res = ft_fill_expand(envp[i], str, index, quote);
			free(str);
			return (res);
		}
		i++;
	}
	return (str);
}

//Function to expand all the environmental variables in the 2D array
void	ft_check_var(char **str, char **env)
{
	int	i;
	int	quote;

	quote = 0;
	while (*str)
	{
		i = 0;
		while (*str && (*str)[i])
		{
			if ((*str)[i] == '"')
				quote++;
			if ((*str)[i] == '\'')
			{
				i++;
				while ((*str)[i] != '\'' && (*str)[i])
					i++;
			}
			else if ((*str)[i] == '$')
				*str = ft_expand_var(env, *str, i, quote % 2);
			i++;
		}
		str++;
	}
}
