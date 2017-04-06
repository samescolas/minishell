/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 19:36:24 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"

char	*prompt(char *p, char *color)
{
	char	*input;

	ft_padstr((p ? p : ">>"), 1, color);
	if (get_next_line(STDIN_FILENO, &input) <= 0)
		return (prompt(p, color));
	else
		return (input);
}

char	*get_color(char *arg)
{
	if (ft_strcmp(arg, "RED") == 0)
		return (RED);
	if (ft_strcmp(arg, "CYAN") == 0)
		return (CY3);
	if (ft_strcmp(arg, "MAGENTA") == 0)
		return (MAG);
	if (ft_strcmp(arg, "BLUE") == 0)
		return (BL2);
	if (ft_strcmp(arg, "BLACK") == 0)
		return (BK2);
	if (ft_strcmp(arg, "DEFAULT") == 0)
		return (DEF);
	sentinel("That's not a color...");
	error:
	return ((void *)0);
}
