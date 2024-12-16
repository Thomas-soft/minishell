/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:30:10 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/21 14:17:34 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigint2(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

int	setup_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	df_int;
	struct termios		term;

	ft_bzero(&sa_int, sizeof(sa_int));
	ft_bzero(&df_int, sizeof(df_int));
	sa_int.sa_handler = &handle_sigint;
	df_int.sa_handler = SIG_DFL;
	signal(SIGQUIT, handle_sigquit);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (ft_perror("sigaction"));
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (-1);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (-1);
	return (0);
}

int	setup_signal2(void)
{
	struct sigaction	sa_int;
	struct termios		term;

	ft_bzero(&sa_int, sizeof(sa_int));
	sa_int.sa_handler = &handle_sigint2;
	signal(SIGQUIT, handle_sigquit);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (ft_perror("sigaction"));
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (-1);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (-1);
	return (0);
}
