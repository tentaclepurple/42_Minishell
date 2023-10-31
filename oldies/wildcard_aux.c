/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:02:32 by imontero          #+#    #+#             */
/*   Updated: 2023/10/31 08:48:54 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../src/parse.h"

int	ft_matlen(char **mat)
{
	int	len;

	len = 0;
	while (mat[len])
		len++;
	return (len);
}

int	count_dir(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry != NULL)
	{
		entry = readdir(dir);
		count++;
	}
	closedir(dir);
	return (count);
}

char	**create_exp_cmdargs(char **cmdargs)
{
	char	**exp_cmdargs;

	exp_cmdargs = malloc(sizeof(char *) * (ft_matlen(cmdargs) * count_dir()));
	ft_bzero(exp_cmdargs, sizeof(char *) * (ft_matlen(cmdargs) * count_dir()));
	exp_cmdargs[0] = ft_strdup(cmdargs[0]);
	return (exp_cmdargs);
}

int	find_wild_match(char *pattern, char *str)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (*pattern == '\0')
				return (1);
			while (*str)
			{
				if (*str == *pattern && find_wild_match(pattern, str))
					return (1);
				str++;
			}
			return (0);
		}
		if (*str == '\0' || (*pattern != *str))
			return (0);
		pattern++;
		str++;
	}
	return (*str == '\0');
}
