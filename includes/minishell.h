/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 13:45:10 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/11 19:31:24 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <sys/wait.h>
#include <unistd.h>

# define MAX_PATHLEN 512
# define MAX_DEPTH
# define NUM_BUILTINS 9

# define DEF "\x1B[0m"
# define RED "\x1B[31m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CY1 "\x1B[36m"
# define CY2 "\x1B[37m"
# define CY3 "\x1B[96m"
# define BK2 "\x1B[90m"
# define BL2 "\x1B[94m"
# define MG2 "\x1B[95m"

typedef struct			s_tkn
{
	void				*data;
	size_t				size;
	struct s_tkn		*next;
	struct s_tkn		*prev;
}						t_tkn;

typedef struct			s_command
{
	char				*path;
	char				**env;
	int					builtin;
	t_tkn				*args;
	struct s_command	*next;
}						t_command;

char		*find_path(char *command, char **envp);
int			valid_bracket(char *command);
int			is_close_bracket(char c);
int			is_open_bracket(char c);
int			is_bracket(char c);
int			get_line(char **line);
void		autocomplete(char *text, unsigned int *cursor_position);
char		**copy_env(char **envp);

void		append_env(char ***envp, char *str);
void		free_command(t_command *command);
t_command	*parse_command(char *command, char **envp);
void		turn_off_ctrl_c(void);
void		reset_settings(void);
int			call_builtin(t_command *command);
int			sftsh_cd(t_command *command);
int			sftsh_echo(t_command *command);
int			sftsh_env(t_command *command);
int			sftsh_exit(t_command *command);
int			builtin(char *command);
int			is_valid_command(char *command);
t_tkn		*get_tokens(char *command);
t_tkn		*create_list_item(void *data, size_t size);
void		append_list(t_tkn **list, t_tkn *node);
int			ft_strcount(char *str, char c);
void		push_list(t_tkn **list, t_tkn *node);
t_tkn		*pop_list(t_tkn **list);
void		change_dir(char *path, char **envp);
char		*get_env(char **envp, char *val);
void		set_env(char **envp, char *variable, char *value);
char		*expand_tilde(char *path, char **envp);
char		**get_args(char *str);
char		*prompt(char *p, char *color);
char		*get_color(char *arg);
int			call_func(char *command, char *envp[]);
int			exec_command(t_command *command);
t_command	*create_command(char *path, t_tkn *args, char **envp);

#endif
