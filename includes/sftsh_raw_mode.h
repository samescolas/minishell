/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_raw_mode.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:53:54 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/08 14:26:15 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFTSH_RAW_MODE_H
# define SFTSH_RAW_MODE_H

# include <termios.h>
# include <unistd.h>
# include <stdlib.h>

struct termios	*sftsh_makeraw(void);
void			reset_terminal_settings(struct termios *default_settings);

#endif
