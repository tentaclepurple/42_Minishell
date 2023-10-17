/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:49:26 by josu              #+#    #+#             */
/*   Updated: 2023/10/17 11:10:07 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

/* ------------- */

int	ft_lines(char *str, char **env)
{
	char	**res;
	t_px	*nodes;

	str = ft_correct_str(str);
	if (!str)
		return (1);
	res = ft_split_str(str, ' ');
	ft_check_var(res, env);
	res = ft_correc_special(res, "<>|&");
	nodes = ft_parse(res, env);
	ft_free_split(res);
	if (!nodes)
		return (1);
	pipex(nodes);
	free(str);
	return (0);
}
/* --------TERMINAL---------- */

/*
	Returns 0 if any mthfckr suppresed env
*/	
int	check_no_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	if (i == 0)
		return (0);
	else
		return (1);
}

int	check_env_and_vars(char **env)
{
	if (check_no_env(env))
		return (1);
	else
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

void	terminal(char **env)
{
	char	*input;
	char	*prompt;

	prompt = get_prompt(env);
	while (1)
	{
		input = readline(prompt);
		if (!input)
			continue ;
		if (!ft_strcmp("exit", input))
		{
			free(input);
			break ;
		}
		add_history(input);
		if (!ft_strcmp("perro", input))
			rl_clear_history();
		if (!ft_strcmp("redisp", input))
			rl_redisplay();
		if (!ft_strcmp("rep", input))
			rl_replace_line("replaced!!", 0);
		//rl_replace_line("replace", 0);
		if (!ft_strcmp("clear", input))
			printf("\033[H\033[2J");
		else
			ft_lines(input, env);
		free (input);
	}
	free(prompt);
}
