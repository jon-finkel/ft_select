/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_window_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 18:43:00 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/31 12:35:42 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			check_window_size(t_data *data)
{
	char				*str;
	struct winsize		w;

	PROTECT(str = tgetstr("cl", NULL), -1);
	NEG_PROTECT(ioctl(data->fd, TIOCGWINSZ, &w), -1);
	data->columns = _MAX((int)((w.ws_col - 5) / data->width), 1);
	data->rows = data->argc / data->columns;
	data->extra = data->argc % data->columns;
	if (data->status == E_HELP)
		return (display_help(data, w.ws_col - 1));
	else
		return (display_files(data, w.ws_col - 1));
}
