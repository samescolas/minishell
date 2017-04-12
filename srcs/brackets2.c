/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 10:27:31 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/07 10:32:13 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_close_bracket(char c)
{
	return (c == ')' || c == ']');
}

int	is_open_bracket(char c)
{
	return (c == '(' || c == '[');
}

int	is_bracket(char c)
{
	return (is_open_bracket(c) || is_close_bracket(c));
}
