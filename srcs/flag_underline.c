/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_underline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 20:25:02 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/26 21:38:16 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			flag_underline(t_flag flag, const int fd)
{
	if (flag == E_ENABLE)
		ft_putstr_fd(tgetstr("us", NULL), fd);
	else
		ft_putstr_fd(tgetstr("ue", NULL), fd);
	KTHXBYE;
}
