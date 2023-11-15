/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:49:26 by josu              #+#    #+#             */
/*   Updated: 2023/11/15 09:17:28 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsebonus.h"

//int	ft_lines(char *str, char **env)
int	ft_lines(char *str, t_info *info)
{
	char	**res;
	t_px	*nodes;
	int		i;

	if (ft_lines2(str, info, &res))
		return (1);
	if (!ft_clean_quotes(res))
		return (ft_free_split(res), 1);
	if (ft_check_inout(res))
		return (ft_free_split(res), 2);
	nodes = ft_parse(res, info);
	ft_free_split(res);
	if (!nodes)
		return (1);
	if (nodes->info->cmd_amount == 1 && nodes->type == BIp)
	{
		if (ft_execbi_parent(nodes))
			return (ft_free_nodes(nodes), 4);
	}
	ft_open_outfiles(nodes);
	i = 0;
	ft_loop_pipex(nodes, &i);
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
		{
			printf("exit\n");
			break ;
		}
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
