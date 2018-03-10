/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_window_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 18:43:00 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/10 20:38:38 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			check_window_size(t_data *data)
{
	struct winsize		w;

	ft_dprintf(data->fd, "%s", tgetstr("cl", NULL));
	ioctl(data->fd, TIOCGWINSZ, &w);
	data->columns = MAX((int)((w.ws_col - 5) / data->width), 1);
	data->rows = data->argc / data->columns;
	data->extra = data->argc % data->columns;
	if (w.ws_col < data->width + 2 || w.ws_row < data->rows)
	{
		ft_printf("WINSIZE TOO SMALL");
		data->lock = true;
		while (w.ws_col < data->width + 2 || w.ws_row < data->rows)
			ioctl(data->fd, TIOCGWINSZ, &w);
	}
	data->lock = false;
	if (data->status == E_HELP)
		GIMME(display_help(data, w.ws_col - 1));
	else
		GIMME(display_files(data, w.ws_col - 1));
}
