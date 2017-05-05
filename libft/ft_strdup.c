/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 11:34:13 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/03 18:45:11 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char *new_str;

	if (!str)
		return ((void *)0);
	new_str = ft_strnew(ft_strlen((char *)str));
	if (new_str)
		ft_strcpy(new_str, (char *)str);
	return (new_str);
}
