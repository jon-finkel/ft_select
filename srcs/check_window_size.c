/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_window_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 18:43:00 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/31 10:48:02 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			check_window_size(t_data *data)
{
	char				*str;
	int					x;
	int					y;
	struct winsize		w;

	PROTECT(str = tgetstr("cl", NULL), -1);
	ft_printf("");
	NEG_PROTECT(ioctl(data->fd, TIOCGWINSZ, &w), -1);
	data->columns = (--w.ws_col - 4) / data->width;
	data->rows = data->argc / _MAX(data->columns, 1);
	data->extra = data->argc % _MAX(data->columns, 1);
	x = _MAX(37, (int)(data->width + 4));
	y = data->rows + (data->extra ? 5 : 4);
	if (data->status == E_HELP)
		y = _MAX(12, y);
	if (w.ws_col >= x && w.ws_row >= y)
	{
		if (data->status == E_HELP)
			NEG_PROTECT(display_help(data, w.ws_col - 1), -1);
		else
			NEG_PROTECT(display_files(data, w.ws_col - 1), -1);
	}
	else
		ft_dprintf(data->fd, "%sWindow size too small!", str);
	return (0);
}
