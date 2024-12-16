/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:38:47 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/14 19:34:37 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_var = 0;

static int	handle_error(void)
{
	rl_clear_history();
	return (0);
}

static int	exec2(t_token **tokens, t_env *env, t_to_free *to_free)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->tab[0] && handle_cmd(tokens + i, env, to_free) == -1)
		{
			free_token(tokens, 1);
			return (-1);
		}
		while ((tokens[i]) && (!is_pr_token(tokens[i]->tab)
				|| tokens[i]->tab[0][0] != '|'))
			i++;
		if (tokens[i] && is_pr_token(tokens[i]->tab)
			&& tokens[i]->tab[0][0] == '|')
			i++;
	}
	return (0);
}

int	exec(char *line, t_env *env)
{
	t_token		**tokens;
	t_to_free	to_free;
	int			res;

	res = 0;
	ft_bzero(&to_free, sizeof(to_free));
	tokens = split_master(line, env, &res);
	if (tokens == NULL && res == 0)
	{
		rl_clear_history();
		return (-1);
	}
	if (res == 1)
		return (handle_error());
	to_free.tokens = tokens;
	to_free.env = env;
	to_free.line = line;
	if (exec2(tokens, env, &to_free) == -1)
		return (-1);
	free_token(tokens, 1);
	return (0);
}
