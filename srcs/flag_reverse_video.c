/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_reverse_video.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 20:21:24 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/26 21:37:53 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			flag_reverse_video(t_flag flag, const int fd)
{
	if (flag == E_ENABLE)
		ft_putstr_fd(tgetstr("mr", NULL), fd);
	else
		ft_putstr_fd(tgetstr("me", NULL), fd);
	KTHXBYE;
}
