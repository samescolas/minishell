/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:39:12 by sescolas          #+#    #+#             */
/*   Updated: 2017/06/26 10:28:52 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sftsh_read_line.h"
#include "../libft/libft.h"
#include "sftsh_vars.h"

static void		resize_buffer(char **line, unsigned int current_size)
{
	char	*tmp;

	tmp = ft_strnew(current_size + BUFF_SIZE);
	ft_strncpy(tmp, *line, current_size);
	ft_strdel(line);
	*line = tmp;
}

static void		key_printable(char c, char *line, unsigned int *chars_copied)
{
	char	bkspc[3];

	if (c == 127)
	{
		if (*chars_copied == 0)
			return ;
		bkspc[0] = 8;
		bkspc[1] = 127;
		bkspc[2] = 8;
		line[--(*chars_copied)] = '\0';
		write(1, bkspc, 3);
		return ;
	}
	if (*chars_copied == 0 && c == ';')
		return ;
	write(1, &c, 1);
	line[(*chars_copied)++] = c;
}

static void		handle_ctrl_c(int sig)
{
	g_ctrl_c_pressed = 1;
	write(1, "\n", 1);
	signal(sig, handle_ctrl_c);
}

int				read_line(char **line)
{
	char			buf;
	int				ret;
	unsigned int	chars_copied;
	void			*prev_sig_action;

	*line = ft_strnew(BUFF_SIZE);
	chars_copied = 0;
	prev_sig_action = signal(SIGINT, handle_ctrl_c);
	while ((ret = read(STDIN_FILENO, &buf, 1)) >= 0 && buf != '\n')
	{
		if (!buf)
			continue ;
		if (g_ctrl_c_pressed)
			resize_buffer(line, (g_ctrl_c_pressed = 0));
		else if (chars_copied > BUFF_SIZE - 1 && chars_copied % BUFF_SIZE == 0)
			resize_buffer(line, chars_copied);
		if (buf == 127 || (ft_isprint(buf) && buf != '\n'))
			key_printable(buf, *line, &chars_copied);
		buf = '\0';
	}
	write(1, "\n", 1);
	signal(SIGINT, prev_sig_action);
	if (chars_copied > 0 || **line != '\0')
		return (1);
	else
		return (-1);
}
