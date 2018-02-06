/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_window_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 18:43:00 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/06 15:09:24 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			check_window_size(t_data *data)
{
	char				*str;
	struct winsize		w;

	FAILZ(str = tgetstr("cl", NULL), -1);
	EPICFAILZ(ioctl(data->fd, TIOCGWINSZ, &w), -1);
	data->columns = MAX((int)((w.ws_col - 5) / data->width), 1);
	data->rows = data->argc / data->columns;
	data->extra = data->argc % data->columns;
	if (data->status == E_HELP)
		GIMME(display_help(data, w.ws_col - 1));
	else
		GIMME(display_files(data, w.ws_col - 1));
}
