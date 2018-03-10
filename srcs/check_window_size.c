/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_window_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 18:43:00 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/10 23:41:55 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			check_window_size(t_data *data)
{
	struct winsize		w;

	ft_dprintf(STDOUT_FILENO, "%s", tgetstr("cl", NULL));
	ft_printf("WINSIZE TOO SMALL");
	data->lock = true;
	ioctl(data->fd, TIOCGWINSZ, &w);
	data->columns = MAX((int)((w.ws_col - 5) / data->width), 1);
	data->rows = data->argc / data->columns;
	data->extra = data->argc % data->columns;
	while ((data->status != E_HELP && (w.ws_row < data->rows + 4
		|| w.ws_col < data->width + 2)) || (data->status == E_HELP
		&& (w.ws_row < 12 || w.ws_col < 40)))
		ioctl(data->fd, TIOCGWINSZ, &w);
	data->lock = false;
	if (data->status == E_HELP)
		GIMME(display_help(data, w.ws_col - 1));
	else
		GIMME(display_files(data, w.ws_col - 1));
}
