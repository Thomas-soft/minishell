/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:11:28 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/14 19:47:06 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	parse_quotes(char *line, int *i)
{
	char	quote;

	quote = 0;
	if (line[*i] == '\'' || line[*i] == '\"')
	{
		quote = line[*i];
		*i += 1;
	}
	while (line[*i] && line[*i] != quote && quote)
		*i += 1;
	if (line[*i] == 0 && quote)
		return (0);
	if (line[*i])
		*i += 1;
	return (1);
}

int	quotes_are_good(char *line)
{
	t_index	i;

	init_index(&i);
	while (line[i.i])
	{
		while (line[i.i] && line[i.i] != '\'' && line[i.i] != '\"')
			i.i++;
		if (!parse_quotes(line, &i.i))
			return (0);
	}
	i.i = 0;
	while (line[i.i] && line[i.i] == ' ')
		i.i++;
	if (line[i.i] == 0)
		return (0);
	return (1);
}

int	pr_are_good(char *line)
{
	t_index	i;

	init_index(&i);
	i.i = 0;
	while (line[i.i])
	{
		while (line[i.i] && line[i.i] != '\'' && line[i.i] != '\"'
			&& line[i.i] != '<' && line[i.i] != '>' && line[i.i] != '|')
			i.i++;
		if (line[i.i] == '<' || line[i.i] == '>' || line[i.i] == '|')
		{
			if (!is_pr(line + i.i))
				return (0);
			parse_and_len_pr(NULL, line, &i);
			while (line[i.i] && line[i.i] == ' ')
				i.i++;
			if (is_pr(line + i.i))
				return (0);
		}
		if (!parse_quotes(line, &i.i))
			return (0);
	}
	return (1);
}

int	good_pos_pr(t_token **tokens)
{
	int	i;

	i = 0;
	if (tokens[0]->type == PR && tokens[0]->tab[0][0] == '|')
		return (-1);
	while (tokens[i])
		i++;
	if (i == 1 && tokens[0]->type == PR)
		return (-1);
	if (i > 1 && tokens[i - 1]->type == PR)
		return (-1);
	return (0);
}
