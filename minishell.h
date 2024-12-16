/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:46:12 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/14 19:44:00 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ==================== function ==================== */

# define CMDERR -1    // command not found
# define CMDCUSTOM -2 // command custom
# define CMD -3       // command
# define ARG_CMD -4   // file and command
# define ARG -6       // files
# define PR -7        // pipes/redirections

/* ==================== include ==================== */

# include "Libft/libft.h"

/* fonctions de manipulation de répertoires (opendir, readdir, etc.) */
# include <dirent.h>
/* variable errno et les codes d'erreur */
# include <errno.h>
/* fonctions de manipulation de fichiers (open, close, etc.) */
# include <fcntl.h>
/* fonctions de gestion des signaux (signal, sigaction, etc.) */
# include <signal.h>
/* fonctions d'entrée/sortie (printf, scanf, etc.) */
# include <stdio.h>
/* fonctions de gestion de la mémoire (malloc, free, etc.) */
# include <stdlib.h>
/* fonctions de manipulation de chaînes de caractères (strerror, etc.) */
# include <string.h>
/* types de données système (pid_t, ssize_t, etc.) */
# include <sys/types.h>
/* fonctions de gestion des processus (wait, waitpid, etc.) */
# include <sys/wait.h>
/* fonctions système Unix (fork, execve, etc.) */
# include <unistd.h>
/* lecture interactive d'une ligne de texte avec édition de ligne */
# include <readline/readline.h>
/* gestion de l'historique des commandes avec readline */
# include <readline/history.h>
/* interactions avec les opérations d'entrée/sortie du système */
# include <sys/ioctl.h>
/* manipulation des informations sur les fichiers et les répertoires */
# include <sys/stat.h>
/* types de données pour les appels système et les structures associées. */
# include <sys/types.h>
# include <termios.h>

/* ==================== structures parsing ==================== */

typedef struct s_index
{
	int				i;
	int				j;
	int				k;
	int				doll;
}					t_index;

typedef struct s_token
{
	int				type;
	char			**tab;
}					t_token;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}					t_env;

typedef struct s_count_redirection
{
	int				l;
	int				r;
}					t_count_redirection;

typedef struct s_exec
{
	int				fd1;
	int				fd2;
	int				pid;
	int				p_fd[2];
	int				res;
}					t_exec;

typedef struct s_to_free
{
	t_token			**tokens;
	t_env			*env;
	char			*line;
}					t_to_free;

/* ==================== parsing ==================== */

t_token				**split_master(char *line, t_env *env, int *res);

/* ==================== parsing token ==================== */

int					count_token(char *line);
int					len_token(char *line);
char				*get_token(char *line, t_index *i);
void				put_types(t_token **tokens);

/* ==================== parsing word ==================== */

int					count_word(char *token_line);
int					len_word(char *token_line, t_env *env);
char				*get_word(char *token_line, int *i, t_env *env);
t_token				*split_word(char *token_line, t_env *env);

/* ==================== parsing verifications ==================== */

int					quotes_are_good(char *line);
int					pr_are_good(char *line);
int					is_quote(char c);
int					is_pr(char *line);
int					is_dollar(char c);
int					is_pr_token(char **tab);
int					good_pos_pr(t_token **tokens);

/* ==================== parsing sorting ==================== */

t_token				**sort_tokens(t_token **tokens, t_env *env);
int					sort_count_tokens(t_token **tokens);
t_token				*get_sort_tokens(t_token **tokens, int k);
int					count_sort_tokens(t_token **tokens);
int					len_cmd_sort(t_token **tokens);
t_token				*get_sort_cmd_tokens(t_token **tokens, t_env *env);

/* ==================== parsing pipe/redirection ==================== */

int					parse_and_len_pr(char *str, char *line, t_index *i);

/* ==================== parsing env ==================== */

int					len_env_token2(char *token_line, int *i, int *len,
						t_env *env);
int					get_env_token2(char *new_token_line, char *token_line,
						t_index *i, t_env *env);
char				*getenv_value(char *s, t_env *env);
char				*get_cmd_path(char *cmd, t_env *env);
int					len_env_token(char *token_line, t_env *env);
int					get_env_token(char *new_token_line, char *token_line,
						t_env *env);
char				*getenv_value(char *s, t_env *env);

/* ==================== parsing utils ==================== */

void				init_index(t_index *index);
void				free_2d_char(char **tab);
void				free_token(t_token **tokens, int tab);
void				err_free_token(t_token **tokens, int j, int tab);
void				err_free_2d_char(char **tab, int j);
size_t				ft_nblen(int nb);
void				ft_putnbr_chr(char *tab, int *j, long int nb);
int					has_cmd(t_token **tokens);
int					has_arg_cmd(t_token **tokens);
char				*ft_strncat(char *dest, char *src, unsigned int size);
char				**initialize_tab(t_token **tokens, t_index *i);

/* ==================== exec env list ==================== */

t_env				*new_list(void);
int					is_empty(t_env *env);
int					list_length(t_env *env);
void				print_list(t_env *env);
t_env				*push_back_list(t_env *env, char *s);
t_env				*push_front_list(t_env *env, char *s);
t_env				*pop_back_list(t_env *env);
t_env				*pop_front_list(t_env *env);
t_env				*pop_element_list(t_env *env, char *s);
t_env				*clear_list(t_env *env);
t_env				*init_env(char **tab_env);
t_env				*dup_env(t_env *env);

/* ==================== exec cmd custom ==================== */

void				ft_echo(char **tab);
int					ft_cd(char **tab, t_env *env);
int					ft_pwd(void);
int					ft_export(char **tab, t_env *env);
void				ft_unset(char **tab, t_env *env);
void				ft_env(t_env *env);
void				ft_exit(t_token **tokens, t_env *env, char *line);

/* ==================== exec signal ==================== */

int					setup_signal(void);
int					setup_signal2(void);

/* ==================== exec heredoc ==================== */

int					get_heredoc(char *end, t_to_free *to_free);

/* ==================== exec utils ==================== */

int					strcmp2(const char *s1, const char *s2, int c);
size_t				ft_strlen_endl(const char *s);
char				*strjoin2(char *s1, char *s2);
int					ft_perror(char *s);
char				**get_env(t_env *old_env);
char				**get_tab(char **old_tab);
int					has_pipe(t_token **tokens);
int					refresh_pwd(t_env *env, char *var);

/* ==================== exec ==================== */

int					exec(char *line, t_env *env);
int					handle_cmd(t_token **tokens, t_env *env,
						t_to_free *to_free);
int					handle_redirections_1(t_token **tokens, t_to_free *to_free);
int					handle_redirections_2(t_token **tokens);
int					execve_cmd(t_token **tokens, t_to_free *to_free);

/* ==================== variable globale ==================== */

extern int			g_var;

#endif
