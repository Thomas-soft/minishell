/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_pr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:21:49 by ttofil            #+#    #+#             */
/*   Updated: 2023/10/26 15:47:36 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_and_len_pr(char *str, char *line, t_index *i)
{
	int	len;

	len = 0;
	while (line[i->i] && (line[i->i] == '>' || line[i->i] == '<'
			|| line[i->i] == '|'))
	{
		if (str != NULL)
			str[i->k++] = line[i->i];
		i->i += 1;
		len++;
	}
	if (str != NULL)
		str[i->k] = '\0';
	return (len);
}

int	is_pr(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == '>' || line[i] == '<' || line[i] == '|'))
		i++;
	if (i == 0)
		return (0);
	if (!ft_strncmp(line, ">", i) || !ft_strncmp(line, ">>", i)
		|| !ft_strncmp(line, "<", i) || !ft_strncmp(line, "<<", i)
		|| !ft_strncmp(line, "|", i))
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if ((c == '\'' || c == '\"'))
		return (1);
	return (0);
}

int	is_pr_token(char **tab)
{
	if (tab[0] && tab[1] == NULL && (!ft_strncmp(tab[0], ">", ft_strlen(tab[0]))
			|| !ft_strncmp(tab[0], "<", ft_strlen(tab[0]))
			|| !ft_strncmp(tab[0], "|", ft_strlen(tab[0]))
			|| !ft_strncmp(tab[0], ">>", ft_strlen(tab[0]))
			|| !ft_strncmp(tab[0], "<<", ft_strlen(tab[0]))))
		return (1);
	return (0);
}

int	has_pipe(t_token **tokens)
{
	int	i;

	i = 0;
	while ((tokens[i]) && (!is_pr_token(tokens[i]->tab)
			|| tokens[i]->tab[0][0] != '|'))
		i++;
	if (tokens[i])
		return (1);
	return (0);
}
