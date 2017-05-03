/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:30:15 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/02 21:48:34 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_help(void)
{
	ft_putendl("there's no such thing as a stupid question");
}

int		sftsh_exit(t_command *command)
{
	if (command->num_args > 0 && ft_strcmp((command->args)[0], "help") == 0)
		print_help();
	exit(0);
}
