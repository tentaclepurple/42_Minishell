/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:49:26 by josu              #+#    #+#             */
/*   Updated: 2023/10/27 11:31:18 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

//int	ft_lines(char *str, char **env)
int	ft_lines(char *str, t_info *info)
{
	char	**res;
	t_px	*nodes;

	str = ft_correct_str(str);
	if (!str)
		return (1);
	res = ft_split_str(str, ' ');
	free (str);
	if (!res)
		return (2);
	if (ft_check_var(res, info->envcp))
		return (ft_free_split(res), 3);
	res = ft_correc_special(res, "<>|&");
	if (!res)
		return (3);
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
	pipex(nodes);
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

//void	terminal(char **env)
void	terminal(t_info *info)
{
	char				*input;
	char				*prompt;
	struct sigaction	sa;

	prompt = get_prompt(info->envcp);
	while (1)
	{
		sa.sa_handler = &ft_handle_client;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
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

/*if (input[0])
	add_history(input);
if (!ft_strcmp("clear", input))
	printf("\033[H\033[2J");*/

void	terminal_options(char *input)
{
	if (input[0])
		add_history(input);
	if (!ft_strcmp("clear", input))
		printf("\033[H\033[2J");
}
