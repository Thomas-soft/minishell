/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:09:56 by ttofil            #+#    #+#             */
/*   Updated: 2023/10/26 19:31:06 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_pipe(char **tab)
{
	if (is_pr_token(tab) && !ft_strcmp(tab[0], "|"))
		return (1);
	return (0);
}

static void	put_types2(t_token **tokens, int i)
{
	while (tokens[i])
	{
		if (is_pr_token(tokens[i]->tab))
			tokens[i]->type = PR;
		else if (i > 0 && tokens[i] && tokens[i]->tab[0] && is_pr_token(tokens[i
					- 1]->tab) && tokens[i - 1]->tab[0][0] != '|'
					&& tokens[i]->tab[1] != NULL)
			tokens[i]->type = ARG_CMD;
		else if (i > 0 && tokens[i] && tokens[i]->tab[0] && is_pr_token(tokens[i
					- 1]->tab) && tokens[i - 1]->tab[0][0] == '>')
			tokens[i]->type = ARG;
		else if (i > 0 && tokens[i] && tokens[i]->tab[0] && is_pr_token(tokens[i
					- 1]->tab) && tokens[i - 1]->tab[0][0] == '<')
			tokens[i]->type = ARG;
		else if (i > 0 && tokens[i] && tokens[i]->tab[0] && is_pr_token(tokens[i
					- 1]->tab) && tokens[i - 1]->tab[0][0] == '|')
			tokens[i]->type = CMD;
		else if (i == 0 && tokens[i] && tokens[i]->tab[0]
			&& !is_pr_token(tokens[i]->tab))
			tokens[i]->type = CMD;
		else
			tokens[i]->type = ARG;
		i++;
	}
}

void	put_types(t_token **tokens)
{
	int	i;
	int	c;

	put_types2(tokens, 0);
	i = 0;
	while (tokens[i])
	{
		c = 0;
		while (tokens[i] && !is_pipe(tokens[i]->tab))
		{
			if ((tokens[i]->type == CMD || tokens[i]->type == ARG_CMD) && c > 0)
				tokens[i]->type = ARG;
			if (tokens[i]->type == CMD || tokens[i]->type == ARG_CMD)
				c++;
			i++;
		}
		if (tokens[i])
			i++;
	}
}
