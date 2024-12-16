/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:04:38 by ttofil            #+#    #+#             */
/*   Updated: 2023/10/26 18:36:12 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_quotes(char *line, t_index *i)
{
	char	quote;

	while (line[i->i] && !is_pr(line + i->i))
	{
		quote = 0;
		while (line[i->i] && !is_quote(line[i->i]) && !is_pr(line + i->i))
			i->i += 1;
		if (is_quote(line[i->i]))
		{
			quote = line[(i->i)++];
			while (line[i->i] && line[i->i] != quote)
				i->i += 1;
			if (line[i->i])
				i->i += 1;
		}
	}
}

int	count_token(char *line)
{
	t_index	i;
	int		len;

	init_index(&i);
	len = 0;
	while (line[i.i])
	{
		while (line[i.i] && line[i.i] == ' ')
			i.i++;
		if (is_pr(line + i.i))
			parse_and_len_pr(NULL, line, &i);
		else
			parse_quotes(line, &i);
		while (line[i.i] && line[i.i] == ' ')
			i.i++;
		len++;
	}
	return (len);
}
