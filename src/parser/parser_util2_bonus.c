/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:59:57 by josu              #+#    #+#             */
/*   Updated: 2023/11/15 09:16:59 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsebonus.h"

//Function to update the cmd_num && cmd_real_num variables
void	ft_num_node_cmd(t_px *nodes)
{
	int	i;
	int	i_init;
	int	cnt;

	i = 0;
	while (i < nodes->info->cmd_amount)
	{
		cnt = 0;
		if (nodes[i].type == CMD || nodes[i].type == BIc)
		{
			i_init = i;
			while (i < nodes->info->cmd_amount && (nodes[i].type == CMD
					|| nodes[i].type == BIc || nodes[i].type == T_PIPE))
				if (nodes[i++].type != T_PIPE)
					cnt++;
			i = i_init;
			while (i < nodes->info->cmd_amount && (nodes[i].type == CMD
					|| nodes[i].type == BIc || nodes[i].type == T_PIPE))
			{
				nodes[i].cmd_real_num = 2 * cnt - 1;
				nodes[i++].cmd_num = cnt;
			}
		}
		i++;
	}
}

//Function to process and fill info of a single node
char	**ft_parse_loop(t_px *node, char **str, char **env)
{
	int		num_arg;

	str = ft_inout_file(node, str);
	if (!ft_is_cm(*str, node))
		node->path = get_cmd_or_cmdpath(env, *str);
	else if (node->type == BIp || node->type == BIc)
		node->path = ft_strdup(*str);
	else
		return (++str);
	num_arg = ft_num_args(str);
	str = ft_fill_full_cmd(node, num_arg, str);
	if (*str)
		str = ft_inout_file(node, str);
	return (str);
}

//Function to init in zeros the array of t_px
t_px	*ft_init_nodes(t_info *info)
{
	t_px	*nodes;
	int		i;

	i = 0;
	nodes = malloc(sizeof(t_px) * info->cmd_amount);
	if (!nodes)
		return (ft_error(MEM, NULL, 2));
	while (i < info->cmd_amount)
	{
		nodes[i].full_cmd = NULL;
		nodes[i].path = NULL;
		nodes[i].infile = NULL;
		nodes[i].outfile = NULL;
		nodes[i].limit = NULL;
		nodes[i].in_flag = 0;
		nodes[i].out_flag = 0;
		nodes[i].type = 0;
		nodes[i].info = info;
		nodes[i].cmd_num = 0;
		i++;
	}
	return (nodes);
}

//Check inapropriate node, returns 0 if OK
int	ft_err_node(t_px node)
{
	if (!node.path && (node.type == CMD || node.type == BIc
			|| node.type == BIp))
		return (ft_error(NCMD, NULL, 127), 2);
	if (!node.full_cmd && (node.type == CMD || node.type == BIc
			|| node.type == BIp))
		return (1);
	if (node.out_flag && !node.outfile)
		return (ft_error(SYNERR, NULL, 20), 4);
	else if (node.out_flag && access(node.outfile, F_OK) < 0)
		return (0);
	else if (node.out_flag && access(node.outfile, W_OK) < 0)
		return (ft_error(NPERM, node.outfile, 126), 5);
	if (node.in_flag == 1 && !node.infile)
		return (ft_error(SYNERR, NULL, 20), 4);
	else if (node.in_flag == 1 && access(node.infile, F_OK) < 0)
		return (ft_error(NDIR, node.infile, 30), 6);
	else if (node.in_flag == 1 && access(node.infile, R_OK) < 0)
		return (ft_error(NPERM, node.infile, 126), 5);
	if (node.in_flag == 2 && !node.limit)
		return (ft_error(SYNERR, NULL, 20), 4);
	if (node.in_flag == 2 && (access(".tmp", F_OK) == 0
			&& access(".tmp", W_OK) < 0))
		return (ft_error(NPERM, ".temp", 126), 5);
	return (0);
}

//Function to check if every malloc filling the nodes where correctly done
int	ft_check_nodes(t_px *nodes)
{
	int	len;
	int	i;

	len = (*nodes).cmd_real_num;
	i = 0;
	while (i < len)
	{
		if (ft_err_node(*(nodes + i)))
			return (1);
		i++;
	}
	return (0);
}
