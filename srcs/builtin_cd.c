/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:20:33 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/11 19:04:20 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sftsh_types.h"
#include "sftsh_expand.h"
#include "sftsh_env.h"
#include <stdarg.h>

static int	sftsh_cd_err(int num_args, ...)
{
	va_list	args;
	char	*msg;
	int		i;

	va_start(args, num_args);
	i = -1;
	while (++i < num_args)
	{
		msg = va_arg(args, char *);
		write(2, msg, ft_strlen(msg));
	}
	write(2, "\n", 1);
	va_end(args);
	return (1);
}

int			sftsh_cd(t_command *command)
{
	char	*full_path;
	char	*cwd;

	if (command->num_args > 2)
		return (sftsh_cd_err(1, "cd: too many arguments"));
	if (command->num_args == 1)
		full_path = ft_strdup(get_env(*command->envp, "HOME"));
	else if (ft_strcmp((command->args)[1], "-") == 0)
	{
		if (!(full_path = ft_strdup(get_env(*command->envp, "OLDPWD"))))
			return (1);
	}
	else
		full_path = command->args[1];
	if (access(full_path, R_OK) == 0)
	{
		cwd = getcwd((void *)0, MAX_PATHLEN);
		set_env(*command->envp, "OLDPWD", cwd);
		chdir(full_path);
		if (full_path != command->args[1])
			ft_strdel(&full_path);
		ft_strdel(&cwd);
		return (0);
	}
	return (sftsh_cd_err(2, "cd: no such file or directory: ", full_path));
	return (1);
}
