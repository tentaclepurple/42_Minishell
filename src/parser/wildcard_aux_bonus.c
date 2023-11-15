/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_aux_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:15:07 by codespace         #+#    #+#             */
/*   Updated: 2023/11/15 09:17:02 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsebonus.h"

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

//Function to fill the complete args array
char	**ft_fill_full_cmd(t_px *node, int num_arg, char **str)
{
	int	i;

	i = 0;
	node->full_cmd = malloc(sizeof(char *) * (num_arg + 1));
	if (node->full_cmd && node->path)
		node->full_cmd[i++] = ft_strdup(node->path);
	else if (node->full_cmd)
		node->full_cmd[i++] = ft_strdup(("null"));
	str++;
	while (i < num_arg && node->full_cmd)
	{
		str = ft_inout_file(node, str);
		node->full_cmd[i] = ft_strdup(*str);
		i++;
		str++;
	}
	if (node->full_cmd)
		node->full_cmd[i] = NULL;
	return (str);
}
