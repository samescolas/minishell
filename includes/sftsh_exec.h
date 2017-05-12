/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_exec.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 19:33:36 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/06 11:35:45 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFTSH_EXEC_H
# define SFTSH_EXEC_H

# include <unistd.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct  s_command t_command;

int		sftsh_exec(t_command *command);

#endif
