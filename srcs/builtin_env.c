/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:18:39 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/15 12:15:06 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "sftsh_types.h"

int			sftsh_env(t_command *command)
{
	char	***envp;
	int		i;

	envp = command->envp;
	i = -1;
	while ((*envp)[++i])
		ft_putendl((*envp)[i]);
	return (0);
}
