/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:33:12 by ttofil            #+#    #+#             */
/*   Updated: 2023/10/25 19:57:26 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_quotes(char *token_line, char *line, t_index *i)
{
	char	quote;

	while (line[i->i] && !is_pr(line + i->i))
	{
		quote = 0;
		while (line[i->i] && !is_quote(line[i->i]) && !is_pr(line + i->i))
			token_line[(i->k)++] = line[(i->i)++];
		if (is_quote(line[i->i]))
		{
			token_line[(i->k)++] = line[i->i];
			quote = line[(i->i)++];
			while (line[i->i] && line[i->i] != quote)
				token_line[(i->k)++] = line[(i->i)++];
			if (line[i->i])
				token_line[(i->k)++] = line[(i->i)++];
		}
	}
	token_line[i->k] = '\0';
}

char	*get_token(char *line, t_index *i)
{
	char	*token_line;

	i->k = 0;
	token_line = malloc(sizeof(char) * (len_token(line + i->i) + 1));
	if (token_line == NULL)
		return (NULL);
	if (is_pr(line + i->i))
		parse_and_len_pr(token_line, line, i);
	else
		parse_quotes(token_line, line, i);
	return (token_line);
}
