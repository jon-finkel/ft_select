/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 20:30:34 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/28 13:48:30 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			color_output(t_data *data)
{
	char		*move;
	char		*str;

	PROTECT(move = tgetstr("cm", NULL), -1);
	PROTECT(str = tgoto(move, data->x, data->y), -1);
	if (data->select[data->pos] == TRUE)
		flag_reverse_video(E_ENABLE);
	ft_printf("%s%s", str, data->argv[data->pos]);
	if (data->select[data->pos] == TRUE)
		flag_reverse_video(E_DISABLE);
	return (0);
}
