/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:09:02 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/03 17:23:47 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_index(t_index *index)
{
	index->i = 0;
	index->j = 0;
	index->k = 0;
	index->doll = 0;
}

char	**initialize_tab(t_token **tokens, t_index *i)
{
	char	**tab;

	tab = malloc(sizeof(char *) * (len_cmd_sort(tokens) + 1));
	if (!tab)
		return (NULL);
	while (tokens[i->i] && tokens[i->i]->type != CMD
		&& tokens[i->i]->type != ARG_CMD)
		i->i++;
	if (!tokens[i->i])
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}

int	has_cmd(t_token **tokens)
{
	int	i;

	i = 0;
	while ((tokens[i]) && (!is_pr_token(tokens[i]->tab)
			|| tokens[i]->tab[0][0] != '|'))
	{
		if (tokens[i]->type == CMD || tokens[i]->type == ARG_CMD)
			return (1);
		i++;
	}
	return (0);
}

int	has_arg_cmd(t_token **tokens)
{
	int	i;

	i = 0;
	while ((tokens[i]) && (!is_pr_token(tokens[i]->tab)
			|| tokens[i]->tab[0][0] != '|'))
	{
		if (tokens[i]->type == ARG_CMD)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strncat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	dest_len;

	i = 0;
	dest_len = (unsigned)ft_strlen(dest);
	while (i < size && src[i] != '\0')
	{
		dest[i + dest_len] = src[i];
		i++;
	}
	dest[i + dest_len] = '\0';
	return (dest);
}
