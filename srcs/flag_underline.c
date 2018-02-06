/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_underline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 20:25:02 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/06 15:13:19 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			flag_underline(t_flag flag, const int fd)
{
	char		*str;

	if (flag == E_ENABLE)
		FAILZ(str = tgetstr("us", NULL), -1);
	else
		FAILZ(str = tgetstr("ue", NULL), -1);
	ft_putstr_fd(str, fd);
	KTHXBYE;
}
