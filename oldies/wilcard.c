/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcard.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:02:32 by imontero          #+#    #+#             */
/*   Updated: 2023/10/30 19:38:51 by imontero         ###   ########.fr       */
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

void	fill_exp_cmdargs(char *pattern, char ***exp_cmdargs)
{
	static int		j = 1;
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	entry = readdir(dir);
	while (entry != NULL)
	{	
		if (find_wild_match(pattern, entry->d_name))
		{
			(*exp_cmdargs)[j] = ft_strdup(entry->d_name);
			j++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
}

void	ft_wildcard(char ***cmdargs)
{
	int		i;
	char	**exp_cmdargs;

	i = 1;
	exp_cmdargs = create_exp_cmdargs(*cmdargs);
	while ((*cmdargs)[i])
	{
		if (ft_strchr((*cmdargs)[i], '*'))
		{
			fill_exp_cmdargs((*cmdargs)[i], &exp_cmdargs);
		}
		i++;
	}
	i = 0;
	//liberar cmdargs;
	//cmdargs = exp_cmdargs;
	while (exp_cmdargs[i])
	{
		printf("el cmdargs expandido %i : %s\n", i, exp_cmdargs[i]);
		i++;
	}
}

int	main()
{
	char	**cmdargs;

	cmdargs = malloc(sizeof(char *) * 10);
	cmdargs[0] = ft_strdup("ls");
	cmdargs[1] = ft_strdup("*no*i*.*x*");
	cmdargs[2] = ft_strdup("*.c");
	cmdargs[3] = ft_strdup("man*");
	cmdargs[4] = ft_strdup("*");
	cmdargs[5] = NULL;
	ft_wildcard(&cmdargs);
	return (0);
}
