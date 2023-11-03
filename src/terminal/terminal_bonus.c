/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:49:26 by josu              #+#    #+#             */
/*   Updated: 2023/11/03 10:54:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse_bonus.h"

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

void	ft_print_nodes(t_px	*nodes)
{
	int	i;
	int	j;
	char	*tipo;

	i = 0;
	while(i < nodes->info->cmd_amount)
	{
		if (nodes[i].type == CMD || nodes[i].type == BIc || nodes[i].type == BIp)
			tipo = "Comando";
		else if (nodes[i].type == T_AND)
			tipo = "AND";
		else if (nodes[i].type == T_OR)
			tipo = "OR";
		else if (nodes[i].type == L_PAR)
			tipo = "L_PAR";
		else if (nodes[i].type == R_PAR)
			tipo = "R_PAR";
		printf("Type: %s - Path: %s\n", tipo, nodes[i].path);
		j = 0;
		printf("Full Args: ");
		while (nodes[i].full_cmd[j])
		{
			printf("*%s*", nodes[i].full_cmd[j]);
			j++;
		}
		printf("\n--------------------------\n");
		i++;
	}
}

//int	ft_lines(char *str, char **env)
int	ft_lines(char *str, t_info *info)
{
	char	**res;
	t_px	*nodes;

	if (ft_lines2(str, info, &res))
		return (1);
	if (!ft_clean_quotes(res))
		return (ft_free_split(res), 1);
	nodes = ft_parse(res, info);
	ft_free_split(res);
	if (!nodes)
		return (1);
	if (nodes->info->cmd_amount == 1 && nodes->type == BIp)
	{
		if (ft_execbi_parent(nodes))
		{
			ft_free_nodes(nodes);
			return (4);
		}
	}
	ft_open_outfiles(nodes);
	//pipex(nodes);
	ft_print_nodes(nodes);
	ft_free_nodes(nodes);
	return (0);
}

/* 
	returns custom prompt with user or just std prompt if user is suppresed. 
	NULL if error
*/
char	*get_prompt(char **env)
{
	int		i;
	int		found;
	char	*user;
	char	*prompt;

	i = 0;
	found = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "USER=", 5))
		{
			user = ft_strjoin(BLUEB, env[i] + 5);
			if (user)
				found++;
			break ;
		}
		i++;
	}
	if (found == 0)
	{
		prompt = ft_strdup(GREENB"minichel42 "X);
		return (prompt);
	}
	prompt = ft_strjoin(user, GREENB"@minichel42 "X);
	return (free(user), prompt);
}

void	ft_set_sig(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_handle_client;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}	

//void	terminal(char **env)
void	terminal(t_info *info)
{
	char				*input;
	char				*prompt;

	prompt = get_prompt(info->envcp);
	while (1)
	{
		ft_set_sig();
		input = readline(prompt);
		if (!input)
			break ;
		terminal_options(input);
		if (ft_strlen(input))
		{	
			if (ft_lines(input, info) == 4)
			{
				free(input);
				break ;
			}
		}
		free (input);
	}
	free(prompt);
}

void	terminal_options(char *input)
{
	if (input[0])
		add_history(input);
	if (!ft_strcmp("clear", input))
		printf("\033[H\033[2J");
}
