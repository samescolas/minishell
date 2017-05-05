/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_atexit.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 10:06:00 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/05 10:11:34 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFTSH_ATEXIT_H
# define SFTSH_ATEXIT_H

struct termios;

void	ft_atexit(int load, struct termios *settings, char ***envp);

#endif
