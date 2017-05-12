/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_raw_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:53:15 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/11 16:47:55 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sftsh_raw_mode.h"

static void		turn_off_keyboard_echo(struct termios *settings)
{
	settings->c_lflag &= ~(ECHO);
}

static void		turn_off_canonical_mode(struct termios *settings)
{
	settings->c_lflag &= ~(ICANON);
}

void			reset_terminal_settings(struct termios *default_settings)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, default_settings);
}

struct termios	*sftsh_makeraw(void)
{
	struct termios	updated_settings;
	struct termios	default_settings;
	struct termios	*ret;

	if (!(ret = (struct termios *)malloc(sizeof(struct termios))))
		return ((void *)0);
	tcgetattr(STDIN_FILENO, &default_settings);
	tcgetattr(STDIN_FILENO, &updated_settings);
	updated_settings.c_iflag &= ~(IXON);
	turn_off_canonical_mode(&updated_settings);
	turn_off_keyboard_echo(&updated_settings);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &updated_settings);
	*ret = default_settings;
	return (ret);
}
