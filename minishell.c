/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:44:30 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/21 17:10:09 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prompt2(char *line, t_env *env)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (0);
	if (!pr_are_good(line))
	{
		ft_putstr_fd("Invalid pipe/redirection/quote\n", 2);
		return (0);
	}
	if (!quotes_are_good(line))
		ft_putstr_fd("Invalid quotes\n", 2);
	else
	{
		if (exec(line, env) == -1)
		{
			rl_clear_history();
			env = clear_list(env);
			return (-1);
		}
	}
	return (0);
}

static int	prompt(t_env *env)
{
	char	*line;

	while (1)
	{
		line = readline("✨ Minishell > ");
		if (line != NULL)
		{
			if (line[0])
			{
				if (prompt2(line, env) == -1)
					return (-1);
				add_history(line);
			}
			free(line);
		}
		else
		{
			rl_clear_history();
			env = clear_list(env);
			ft_putstr_fd("exit\n", 1);
			break ;
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **tab_env)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	if (setup_signal() == -1)
		return (-1);
	if (tab_env != NULL && tab_env[0] != NULL && tab_env[0][0] != '\0')
	{
		env = init_env(tab_env);
		if (env == NULL)
			return (-1);
	}
	else
		env = new_list();
	if (prompt(env) == -1)
		return (-1);
	return (0);
}
