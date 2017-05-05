/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:30:15 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/05 10:11:02 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sftsh_atexit.h"

int		sftsh_exit(t_command *command)
{
	ft_atexit(0, (void *)0, (void *)0);
	return (0);
}
