/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:18:46 by codespace         #+#    #+#             */
/*   Updated: 2023/11/08 14:50:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parse_bonus.h"

int	compute_expr(char **nodes, int *i, int min_prec, int nnodes_len);

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				sign;
	int				nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

int	ft_get_prec(char *c)
{
	if (*c == '+' || *c == '-')
		return (1);
	else if (*c == '*' || *c == '/')
		return (2);
	else if (*c == '(')
		return (8);
	else if (*c == ')')
		return (9);
	return (0);
}

int	compute_atom(char **nodes, int *i, int nodes_len)
{
	int	res;
	
	if (ft_get_prec(nodes[*i]) == 8)
	{
		(*i)++;
		res = compute_expr(nodes, i, 1, nodes_len);
		if (ft_get_prec(nodes[*i]) != 9)
			return (printf("unmatched '('"), 9999);
		(*i)++;
		return (res);
	}
	else if (ft_get_prec(nodes[*i]) != 0)
		return (printf("Expecting a command not an operator"), 9999);
	else
	{
		res = ft_atoi(nodes[(*i)]);
		(*i)++;
		return (res);
	}
}

int	compute_op(char *op, int lhs, int rhs)
{
	if ((*op) == '+')
		return (lhs + rhs);
	else if ((*op) == '-')
		return (lhs - rhs);
	else if ((*op) == '*')
		return (lhs * rhs);
	else if ((*op) == '/')
		return (lhs / rhs);
	else
		return(printf("Unknown operator"), 9999);
}

int	compute_expr(char **nodes, int *i, int min_prec, int nodes_len)
{
	int	prec;
	int	next_min_prec;
	int	atom_rhs;
	int	atom_lhs;
	char	*op;
	
	atom_lhs = compute_atom(nodes, i, nodes_len);
	if (atom_lhs == 9999)
		return (9999);
	while (*i < nodes_len)
	{
		op = nodes[(*i)];
		prec = ft_get_prec(nodes[(*i)]);
		if (prec < min_prec || prec > 8)
			break ;
		next_min_prec = prec + 1;
		(*i)++;
		atom_rhs = compute_expr(nodes, i, next_min_prec, nodes_len);
		atom_lhs = compute_op(op, atom_lhs, atom_rhs);
		if (atom_lhs == 9999)
			return (9999);
	}
	return (atom_lhs);
}

int	main(void)
{
	char	*expr = "( 2 + 2 ) * 3";
	char	**split;
	int i = 0;

	split = ft_split(expr, ' ');
	//split[0] = "56";
	//split[1] = "/";
	//split[2] = "2";
	printf("Result: %i\n", compute_expr(split, &i, 1, 7));
	return (0);
}