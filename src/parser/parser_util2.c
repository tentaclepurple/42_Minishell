/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:59:57 by josu              #+#    #+#             */
/*   Updated: 2023/11/14 18:34:48 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse.h"

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
			ft_free_split(nodes[i].full_cmd);
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

//Returns the str info into an array of t_px
//Mallocs space for array of t_px and for the general info
//It does not free the str
//t_px	*ft_parse(char **str, char **env)
t_px	*ft_parse(char **str, t_info *info)
{
	t_px	*nodes;
	int		i;

	i = 0;
	info->cmd_amount = ft_node_quant(str);
	info->fd = NULL;
	nodes = ft_init_nodes(info);
	if (!nodes)
		return (free(info), NULL);
	while (i < info->cmd_amount)
	{
		str = ft_parse_loop(&nodes[i], str, info->envcp);
		i++;
	}
	if (ft_check_nodes(nodes))
		return (ft_free_nodes(nodes), NULL);
	return (nodes);
}

void	ft_stat_signaled(void)
{
	if (WIFSIGNALED(g_stat))
	{
		if (WTERMSIG(g_stat) == 2)
			g_stat = 130;
		else if (WTERMSIG(g_stat) == 3)
			g_stat = 131;
	}
	else
		g_stat = WEXITSTATUS(g_stat);
}

void	pipex_p_aux(t_px *px, int i, pid_t pid)
{
	struct sigaction	sa;

	if (pid == 0)
		ft_child(&px[i], i);
	ft_fd_close(px, i);
	waitpid(pid, &g_stat, 0);
	ft_stat_signaled();
	sa.sa_handler = &ft_2nd_handler;
	sigaction(SIGQUIT, &sa, NULL);
}
