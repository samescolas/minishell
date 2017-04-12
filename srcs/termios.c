/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 09:48:00 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/11 19:55:17 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"
#include <termios.h>
//#include <ctype.h>

struct termios	default_settings;

void	reset_settings(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &default_settings);
}

void	turn_off_ctrl_c(void)
{
	struct termios	updated_settings;

	tcgetattr(STDIN_FILENO, &default_settings);
	atexit(reset_settings);
	tcgetattr(STDIN_FILENO, &updated_settings);
	updated_settings.c_iflag &= ~(IXON);
	updated_settings.c_lflag &= ~(ISIG | ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &updated_settings);
}
