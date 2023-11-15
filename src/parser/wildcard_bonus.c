/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:02:32 by imontero          #+#    #+#             */
/*   Updated: 2023/10/31 20:15:22 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsebonus.h"

char	**create_exp_cmdargs(char **cmdargs, int *size)
{
	char	**exp_cmdargs;

	*size = (ft_matlen(cmdargs) * count_dir()) + 1;
	exp_cmdargs = malloc(sizeof(char *) * (*size));
	ft_bzero(exp_cmdargs, sizeof(char *) * (ft_matlen(cmdargs) * count_dir()));
	exp_cmdargs[0] = ft_strdup(cmdargs[0]);
	return (exp_cmdargs);
}

//Returns 1 if there is a wildcard, 0 if not
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

void	fill_exp_cmdargs(char *pattern, char ***exp_cmdargs, int *j)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!ft_strcmp("*", pattern))
		{
			if (entry->d_name[0] != '.')
			{
				(*exp_cmdargs)[*j] = ft_strdup(entry->d_name);
				(*j)++;
			}
		}
		else if (find_wild_match(pattern, entry->d_name))
		{
			(*exp_cmdargs)[*j] = ft_strdup(entry->d_name);
			(*j)++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
}

char	**trim_excess(char **exp, int size)
{
	char	**trim;
	int		len;
	int		i;

	(void)size;
	len = ft_matlen(exp);
	trim = malloc(sizeof(char *) * (len + 1));
	trim[len] = NULL;
	i = 0;
	while (i < len)
	{
		trim[i] = ft_strdup(exp[i]);
		i++;
	}
	ft_free_split(exp);
	return (trim);
}

void	ft_wildcard(t_px *node)
{
	int		i;
	int		size;
	char	**exp_cmdargs;
	int		j;

	i = 0;
	if (!node->full_cmd)
		return ;
	j = 1;
	exp_cmdargs = create_exp_cmdargs(node->full_cmd, &size);
	while ((node->full_cmd)[++i])
	{
		if (ft_strchr((node->full_cmd)[i], '*'))
			fill_exp_cmdargs((node->full_cmd)[i], &exp_cmdargs, &j);
		else
			exp_cmdargs[j++] = ft_strdup((node->full_cmd)[i]);
	}
	exp_cmdargs = trim_excess(exp_cmdargs, size);
	i = 0;
	while (exp_cmdargs[i])
	{
		i++;
	}
	ft_free_split(node->full_cmd);
	node->full_cmd = exp_cmdargs;
}

/*int	main()
{
	char	**cmdargs;

	cmdargs = malloc(sizeof(char *) * 10);
	cmdargs[0] = ft_strdup("ls");
	//cmdargs[1] = ft_strdup("*no*i*.*x*");
	cmdargs[1] = ft_strdup("*");
	cmdargs[2] = ft_strdup("man*");
	cmdargs[3] = ft_strdup("*a*t*.*");
	cmdargs[4] = NULL;
	ft_wildcard(&cmdargs);
	ft_free_split(cmdargs);
	return (0);
}*/
