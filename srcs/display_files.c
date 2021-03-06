/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 18:28:37 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/10 19:21:46 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int			display_text(t_data *data, char *move, int nb,
					unsigned short ws_col)
{
	char		*str;
	int			k;
	int			x;
	wchar_t		hor_line[ws_col];

	k = -1;
	while (++k < ws_col - 1)
		hor_line[k] = 0x2500;
	hor_line[k] = L'\0';
	str = tgoto(move, 1, 0);
	ft_dprintf(data->fd, "%s%S", str, hor_line);
	x = (ws_col - (ws_col < 61 ? 11 : 56)) / 2;
	str = tgoto(move, x, 0);
	if (ws_col < 61)
		ft_dprintf(data->fd, "%s {1c}ft_select{eoc} ", str);
	else
		ft_dprintf(data->fd, "%s {1c}ft_select - an interactive file selector"\
			", by {1b}Jon Finkel{eoc} ", str);
	str = tgoto(move, 1, nb + 3);
	ft_dprintf(data->fd, "%s%S", str, hor_line);
	str = tgoto(move, ws_col - 21, nb + 3);
	ft_dprintf(data->fd, "%s {H}Press TAB for help{eoc} ", str);
	KTHXBYE;
}

static int			display_frame(t_data *data, unsigned short ws_col)
{
	char		*move;
	char		*str;
	int			nb;

	nb = data->rows + (data->extra ? 1 : 0);
	str = tgetstr("cl", NULL);
	ft_putstr_fd(str, data->fd);
	move = tgetstr("cm", NULL);
	str = tgoto(move, 0, 0);
	ft_dprintf(data->fd, "%s%C", str, 0x256D);
	str = tgoto(move, 0, nb + 3);
	ft_dprintf(data->fd, "%s%C", str, 0x2570);
	str = tgoto(move, ws_col, 0);
	ft_dprintf(data->fd, "%s%C", str, 0x256E);
	str = tgoto(move, ws_col, nb + 3);
	ft_dprintf(data->fd, "%s%C", str, 0x256F);
	display_text(data, move, nb, ws_col);
	KTHXBYE;
}

static int			column_display(t_data *data, int column, int rows)
{
	char		*move;
	int			k;
	int			x;
	int			y;

	rows += data->rows;
	move = tgetstr("cm", NULL);
	x = column * data->width + data->padding * (column + 1) + 2;
	y = 2;
	k = -1;
	while (++k < rows)
	{
		if (data->argc == data->pos)
			flag_underline(E_ENABLE, data->fd);
		color_output(data, data->argc, x, y++);
		if (data->argc == data->pos)
			flag_underline(E_DISABLE, data->fd);
		++data->argc;
	}
	KTHXBYE;
}

int					display_files(t_data *data, unsigned short ws_col)
{
	int					columns;
	short				extra;

	data->padding = ws_col - data->width * data->columns;
	data->padding /= data->columns + 1;
	data->argc = 0;
	get_coordinates(data);
	extra = data->extra;
	display_frame(data, ws_col);
	columns = -1;
	while (++columns < data->columns)
	{
		column_display(data, columns, (extra > 0 ? 1 : 0));
		--extra;
	}
	KTHXBYE;
}
