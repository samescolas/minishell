/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:12:50 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/15 13:10:49 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFTSH_TYPES_H
# define SFTSH_TYPES_H

typedef struct			s_command
{
	char				*path;
	int					builtin_id;
	int					num_args;
	char				**args;
	char				***envp;
	struct s_command	*next;
}						t_command;

t_command				*create_command(char **args, char ***env, int num_args);
t_command				*pop_command(t_command **stack);
void					add_command(t_command **queue, t_command *command);
void					free_command(t_command *command);

#endif
