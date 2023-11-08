/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:18:46 by codespace         #+#    #+#             */
/*   Updated: 2023/11/08 11:59:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/parse_bonus.h"

t_px	compute_atom(t_px *nodes, int *i)
{
	if (nodes[*i].type == L_PAR)
	{
		(*i)++;
		compute_expr(nodes, i);
		if (nodes[*i].type != R_PAR)
			printf("unmatched '('");
		(*i)++;
		//return (computed_expression PIPE)
	}
	else if (nodes[*i].type != CMD)
		printf("Expecting a command not an operator");
	else
	{
		(*i)++;
		return (nodes[(*i) - 1]);
	}
}

int	ft_get_prec(t_px node)
{
	if (node.type == T_AND || node.type == T_OR)
		return (1);
	else if (node.type == T_PIPE)
		return (2);
}

void	compute_expr(t_px *nodes, int *i, int min_prec)
{
	int	prec;
	int	next_min_prec;
	
	//atom_lhs = result from com_atom --> (PIPE)
	while (1)
	{
		prec = ft_get_prec(nodes[(*i)]);
		if ((nodes[*i].type != T_AND && nodes[*i].type != T_OR
			&& nodes[*i].type != T_PIPE) || prec < min_prec)
			break ;
		next_min_prec = prec + 1;
		(*i)++;
		//atom_rhs = compute_expr(nodes, i, next_min_prec);
		//atom_lhs = execute(op, atom_lhs, atom_rhs)
	}
	//return (atom_lhs);
}