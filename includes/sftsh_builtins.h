/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_builtins.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:02:50 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/03 12:17:53 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFTSH_BUILTINS_H
# define SFTSH_BUILTINS_H

# define NUM_BUILTINS 9

typedef struct s_command t_command;

int		find_builtin(char *command);
int		call_builtin(t_command *command);
int		sftsh_cd(t_command *command);
int		sftsh_env(t_command *command);
int		sftsh_setenv(t_command *command);
int		sftsh_unsetenv(t_command *command);
int		sftsh_echo(t_command *command);
int		sftsh_exit(t_command *command);

#endif
