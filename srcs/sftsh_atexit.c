/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_atexit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 09:59:53 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/14 12:21:45 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sftsh_raw_mode.h"
#include "sftsh_env.h"

void	ft_atexit(int load, struct termios *default_settings, char ***envp)
{
	static struct termios	*loaded_settings;
	static char				***loaded_envp;

	if (load)
	{
		loaded_settings = default_settings;
		loaded_envp = envp;
		return ;
	}
	if (loaded_envp)
	{
		delete_env(loaded_envp);
		free(*loaded_envp);
		loaded_envp = (void *)0;
	}
	if (loaded_settings)
		reset_terminal_settings(loaded_settings);
	exit(0);
}
