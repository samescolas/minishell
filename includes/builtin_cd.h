/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 12:10:09 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/15 13:06:20 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

# include <stdarg.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_command	t_command;

int		sftsh_cd(t_command *cmd);

#endif
