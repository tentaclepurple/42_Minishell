/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:59:57 by josu              #+#    #+#             */
/*   Updated: 2023/11/13 10:01:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse_bonus.h"

//Function to free the nodes array
void	ft_free_nodes(t_px *nodes)
{
	int	len;
	int	i;

	len = (*nodes).info->cmd_amount;
	i = 0;
	while (i < len)
	{
		if (nodes[i].full_cmd)
		{
			ft_free_split(nodes[i].full_cmd);
		}
		if (nodes[i].path)
			free(nodes[i].path);
		if (nodes[i].infile)
			free(nodes[i].infile);
		if (nodes[i].outfile)
			free(nodes[i].outfile);
		if (nodes[i].limit)
			free(nodes[i].limit);
		i++;
	}
	free(nodes);
}
void	ft_print_nodes(t_px	*nodes);

//Returns the str info into an array of t_px
//Mallocs space for array of t_px and for the general info
//It does not free the str
t_px	*ft_parse(char **str, t_info *info)
{
	t_px	*nodes;
	int		i;

	i = 0;
	info->cmd_amount = ft_node_quant(str);
	info->fd = NULL;
	nodes = ft_init_nodes(info);
	if (!nodes)
		return (ft_free_info(info), NULL);
	while (i < info->cmd_amount)
	{
		str = ft_parse_loop(&nodes[i], str, info->envcp);
		ft_wildcard(&nodes[i]);
		i++;
	}
	ft_num_node_cmd(nodes);
	if (ft_check_nodes(nodes))
		return (ft_free_nodes(nodes), NULL);
	return (nodes);
}

void	ft_stat_signaled(void)
{
	if (WIFSIGNALED(g_stat))
		g_stat = 130;
	else
		g_stat = WEXITSTATUS(g_stat);
}
