/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:26:42 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/08 18:23:46 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_custom_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 0)
		return (0);
	if (!ft_strncmp(cmd, "echo", i) || !ft_strncmp(cmd, "cd", i)
		|| !ft_strncmp(cmd, "pwd", i) || !ft_strncmp(cmd, "export", i)
		|| !ft_strncmp(cmd, "unset", i) || !ft_strncmp(cmd, "env", i)
		|| !ft_strncmp(cmd, "exit", i))
		return (1);
	return (0);
}

static char	*get_cmd_path2(char *cmd, char *ptr)
{
	int		len;
	char	dir[512];

	while (*ptr)
	{
		len = 0;
		while (*ptr && *ptr != ':')
			dir[len++] = *ptr++;
		if (*ptr && *ptr == ':')
			ptr++;
		dir[len] = '\0';
		ft_strncat(dir, "/", 1);
		ft_strncat(dir, cmd, ft_strlen(cmd));
		if (access(dir, X_OK | F_OK) == 0)
			return (ft_strdup(dir));
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	*path;
	char	*ptr;
	char	*new_cmd;

	if (access(cmd, X_OK | F_OK) == 0)
		return (ft_strdup(cmd));
	if (is_custom_cmd(cmd))
		return (ft_strdup(cmd));
	path = getenv_value("PATH", env);
	if (path == NULL)
		return (ft_strdup(cmd));
	ptr = path;
	new_cmd = get_cmd_path2(cmd, ptr);
	if (new_cmd != NULL)
	{
		free(path);
		return (new_cmd);
	}
	free(path);
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	g_var = 127;
	return (ft_strdup("0"));
}
