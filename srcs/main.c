/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/15 12:21:45 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sftsh.h"
#include "sftsh_env.h"
#include "sftsh_atexit.h"
#include "sftsh_raw_mode.h"

int		main(int argc, char **argv, char **envp)
{
	struct termios	*default_settings;
	char			**envp_cpy;

	if (argc > 2 || argv[1])
	{
		write(1, "sftsh: please start me and type stuff like a human\n", 51);
		return (0);
	}
	default_settings = sftsh_makeraw();
	envp_cpy = copy_env(envp);
	ft_atexit(1, default_settings, &envp_cpy);
	if (sftsh(&envp_cpy) != 0)
		write(2, "unable to read from environment\n", 22);
	return (0);
}
