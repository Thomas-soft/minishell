/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:50:44 by ttofil            #+#    #+#             */
/*   Updated: 2023/10/26 18:37:57 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_word2(char *token_line, int *i)
{
	char	quote;

	while (token_line[*i] && token_line[*i] != ' '
		&& !is_quote(token_line[*i]))
		*i += 1;
	if (token_line[*i] == 0)
		return (1);
	while (token_line[*i] && token_line[*i] != ' ')
	{
		quote = 0;
		while (token_line[*i] && token_line[*i] != ' '
			&& !is_quote(token_line[*i]))
			*i += 1;
		if (is_quote(token_line[*i]))
			quote = token_line[(*i)++];
		while (token_line[*i] && token_line[*i] != quote && quote != 0)
			*i += 1;
		if (token_line[*i] == quote && quote != 0)
			*i += 1;
	}
	return (1);
}

int	count_word(char *token_line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (token_line[i])
	{
		while (token_line[i] && token_line[i] == ' ')
			i++;
		if (token_line[i] == 0)
			break ;
		len += count_word2(token_line, &i);
		while (token_line[i] && token_line[i] != ' ')
			i++;
	}
	return (len);
}
