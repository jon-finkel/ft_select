/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_reverse_video.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 20:21:24 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/27 20:24:46 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			flag_reverse_video(t_flag flag)
{
	char		*str;

	if (flag == E_ENABLE)
		PROTECT(str = tgetstr("mr", NULL), -1);
	else
		PROTECT(str = tgetstr("me", NULL), -1);
	ft_putstr(str);
	return (0);
}
