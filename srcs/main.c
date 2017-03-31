/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 19:36:24 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int		main(void)
{
	char	*command;
	char	**args;

	write(1, ">> ", 3);
	while (get_next_line(0, &command))
	{
		if (ft_strcmp(command, "\r") == 0)
			break ;
		if (ft_strncmp(command, "echo", 4) == 0)
		{
			if ((args = get_args(command)))
			{
				while (*args)
				{
					ft_putendl(*(args++));
				}
			}
			else
				write(1, "\n", 1);
		}
		write(1, ">> ", 3);
	}
	return (0);
}
