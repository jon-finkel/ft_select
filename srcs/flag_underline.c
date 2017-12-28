/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_underline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 20:25:02 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/27 20:26:15 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			flag_underline(t_flag flag)
{
	char		*str;

	if (flag == E_ENABLE)
		PROTECT(str = tgetstr("us", NULL), -1);
	else
		PROTECT(str = tgetstr("ue", NULL), -1);
	ft_putstr(str);
	return (0);
}
