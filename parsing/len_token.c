/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:23:54 by ttofil            #+#    #+#             */
/*   Updated: 2023/10/25 20:03:04 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	parse_quotes(char *line, t_index *i)
{
	int		len;
	char	quote;

	len = i->i;
	while (line[i->i] && !is_pr(line + i->i))
	{
		quote = 0;
		while (line[i->i] && !is_quote(line[i->i]) && !is_pr(line + i->i))
			i->i += 1;
		if (is_quote(line[i->i]))
		{
			quote = line[i->i];
			i->i += 1;
			while (line[i->i] && line[i->i] != quote)
				i->i += 1;
			if (line[i->i])
				i->i += 1;
		}
	}
	len = i->i - len;
	return (len);
}

int	len_token(char *line)
{
	t_index	i;
	int		len;

	init_index(&i);
	len = 0;
	if (is_pr(line + i.i))
		len += parse_and_len_pr(NULL, line, &i);
	else
		len += parse_quotes(line, &i);
	return (len);
}
