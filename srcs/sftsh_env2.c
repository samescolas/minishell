/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 12:48:52 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/11 15:08:59 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env(char ***envp)
{
	ft_strarrdel(envp);
}

char	**create_env(char ***envp)
{
	char	**ret;
	char	*cwd;

	cwd = getcwd((void *)0, MAX_PATHLEN);
	if (!(ret = (char **)malloc(6 * sizeof(char *))))
		return ((void *)0);
	ret[0] = ft_strjoin(ft_strdup("PWD="), cwd);
	ret[1] = ft_strdup("TERM=xterm-256color");
	ret[2] = ft_strdup(\
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki");
	ret[3] = ft_strjoin(ft_strdup("HOME="), cwd);
	ret[4] = ft_strjoin(ft_strdup("OLDPWD="), cwd);
	ret[5] = (void *)0;
	*envp = ret;
	ft_strdel(&cwd);
	return (ret);
}
