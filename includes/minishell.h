/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:31:14 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/23 17:13:15 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h> // strerror
# include <errno.h> // errno
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <linux/limits.h>

extern int	g_sig;

# define EXIT_MAX 9223372036854775807

/*----------------------------- STRUCTURES ----------------------------*/

typedef enum e_enum
{
	pip, // |
	inredir, // <
	outredir, // >
	append, // >>
	heredoc, // <<
	command,
	ms_echo,
	ms_cd,
	ms_pwd,
	ms_export,
	ms_unset,
	ms_env,
	ms_exit,
}	t_tok;

typedef struct s_env
{
	char			*env;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_input
{
	char			**data;
	t_tok			tok;
	t_env			*env;
	struct s_input	*next;
	struct s_input	*prev;
	struct s_input	*head;
	int				status;
}	t_input;

typedef struct s_fd
{
	int		pfd[2];
	int		hfd;
	int		ffd;
	int		pid;
	int		tmpin;
	size_t	pnb;
}	t_fd;

/*----------------------------- COMMON FUNCTIONS -----------------------------*/

// lst_utils -----------------

/* input_lst_utils.c */
void	input_freelst(t_input **lst);
void	input_addback(t_input **lst, t_input *node);
t_input	*input_newnode(char **data, int token, t_env *env);

/* env_lst_utils.c */
void	env_freelst(t_env **env);
void	env_addback(t_env **env, t_env *node);
t_env	*env_newnode(char *data);

// utils ---------------------

/* error_handling.c */
void	fatal_exit(t_input **lst, int rv, char *error_message);
void	*print_error(int error_code, char *error_message);
int		verror(char *s1, char *s2, char *s3);
void	exit_no_input(t_env **env, char *line, int status);

// builtins ------------------

/* exec_builtins.c */
void	*exec_builtin(t_input **in);
void	*handle_bt_nopipe(t_fd *fd, t_input *tmp);

/* exec_builtins_utils.c */
t_input	*builtin_true(t_input *in);

// bt_functs -----------------

/* cd_canon_form.c */
char	*prep_path(char *var, char *path);

/* cd_utils.c */
int		check_directory(char *var, char *path);
int		pwds(t_input *in, char *path);
char	*check_len(char	*path, t_env *env);

/* cd.c */
int		cd(t_input *in);

/* echo.c */
int		echo(char **data);

/* env.c */
int		env(t_input *in);

/* exit.c */
int		mh_exit(char **line, t_input *in);

/* export_utils.c */
int		sort_env(t_env	*env);

/* export.c */
int		export(t_input **in);

/* pwd.c */
int		pwd(t_env *env);

/* unset.c */
int		unset(t_input	**in);

/* builtin_utils.c */
char	*split_wsep(char *str, char sep);
char	*find_var_env(t_env *env, char *var);
void	*exprt_inenv(t_env **env, char *data);

/*----------------------------------------------------------------------------*/

#endif