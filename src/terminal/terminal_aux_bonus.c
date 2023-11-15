/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_aux_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:52:56 by imontero          #+#    #+#             */
/*   Updated: 2023/11/15 09:17:25 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsebonus.h"

int	ft_lines2(char *str, t_info *info, char ***res)
{
	str = ft_correct_str(str);
	if (!str)
		return (1);
	*res = ft_split_str(str, ' ');
	free (str);
	if (!(*res))
		return (2);
	if (ft_check_var(*res, info->envcp))
		return (ft_free_split(*res), 3);
	*res = ft_correc_special(*res, "<>|&");
	if (!(*res))
		return (3);
	return (0);
}

void	ft_open_outfiles(t_px *nodes)
{
	int	i;
	int	fd;

	i = 0;
	while (i < nodes->info->cmd_amount)
	{
		if (nodes[i].outfile)
		{
			fd = open(nodes[i].outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			close(fd);
		}
		i++;
	}
}

//Function to advance i to the next possibly eectuable command
void	ft_advance_unused(t_px *nodes, int *i)
{
	int	par;

	par = 0;
	if (nodes[*i].type == L_PAR)
	{
		par = 1;
		(*i)++;
		while (*i < nodes->info->cmd_amount && par)
		{
			if (nodes[*i].type == L_PAR)
				par++;
			else if (nodes[*i].type == R_PAR)
				par--;
			(*i)++;
		}
		(*i)++;
	}
	else if (*i < nodes->info->cmd_amount)
		*i += nodes[*i].cmd_real_num;
}

//Function to execute pipex repeatedly deppending on
//commands &&, || and ()
void	ft_loop_pipex(t_px *nodes, int *i)
{
	t_type	tp;

	while (*i < nodes->info->cmd_amount)
	{
		tp = nodes[*i].type;
		if (tp == L_PAR || tp == R_PAR || tp == T_AND || tp == T_OR)
			(*i)++;
		if (tp == L_PAR)
		{
			ft_loop_pipex(nodes, i);
			continue ;
		}
		else if (tp == R_PAR)
			return ;
		else if ((tp == T_AND && g_stat == 0) || (tp == T_OR && g_stat != 0))
			continue ;
		else if ((tp == T_AND && g_stat != 0) || (tp == T_OR && g_stat == 0)
			|| ft_check_nodes(&nodes[*i]))
		{
			ft_advance_unused(nodes, i);
			continue ;
		}
		pipex(&nodes[*i]);
		*i += nodes[*i].cmd_real_num;
	}
}
