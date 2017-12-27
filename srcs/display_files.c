/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 18:28:37 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/27 17:49:44 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void			display_frame(char *move, int nb, unsigned short ws_col)
{
	char		*str;
	int			k;
	wchar_t		hor_line[ws_col];

	EXIT_PROTECT(str = tgetstr("cl", NULL));
	ft_putstr(str);
	EXIT_PROTECT(str = tgoto(move, 0, 0));
	ft_printf("%s%C", str, 0x256D);
	EXIT_PROTECT(str = tgoto(move, 0, nb + 3));
	ft_printf("%s%C", str, 0x2570);
	EXIT_PROTECT(str = tgoto(move, ws_col, 0));
	ft_printf("%s%C", str, 0x256E);
	EXIT_PROTECT(str = tgoto(move, ws_col, nb + 3));
	ft_printf("%s%C", str, 0x256F);
	k = -1;
	while (++k < ws_col - 1)
		hor_line[k] = 0x2500;
	hor_line[k] = L'\0';
	EXIT_PROTECT(str = tgoto(move, 1, 0));
	ft_printf("%s%S", str, hor_line);
	EXIT_PROTECT(str = tgoto(move, (ws_col - 56) / 2, 0));
	ft_printf("%s {1c}ft_select - an interactive file selector"\
		", by {1b}Jon Finkel{eoc} ", str);
	EXIT_PROTECT(str = tgoto(move, 1, nb + 3));
	ft_printf("%s%S", str, hor_line);
}

static void			column_display(t_data *data, int column, unsigned short col,
					short extra)
{
	char		*move;
	char		*str;
	int			x;
	int			y;

	EXIT_PROTECT(move = tgetstr("cm", NULL));
	x = (col - data->width * data->columns) / (data->columns + 1);
	data->padding = x;
	get_coordinates(data);
	x = column * data->width + data->padding * (column + 1) + 2;
	y = 2;
	column = -1;
	while (++column < data->rows + extra)
	{
		EXIT_PROTECT(str = tgoto(move, x, y));
		if (data->argc == data->pos)
			ft_printf("%s{4}%s{eoc}", str, data->argv[data->argc]);
		else
			ft_printf("%s%s", str, data->argv[data->argc]);
		++data->argc;
		++y;
	}
}

int					display_files(t_data *data)
{
	char				*move;
	int					columns;
	short				extra;
	struct winsize		w;

	NEG_PROTECT(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w), -1);
	--w.ws_col;
	data->columns = (w.ws_col - 4) / data->width;
	data->rows = data->argc / data->columns;
	data->extra = data->argc % data->columns;
	extra = data->extra;
	EXIT_PROTECT(move = tgetstr("cm", NULL));
	display_frame(move, data->rows + (data->extra ? 1 : 0), w.ws_col);
	data->argc = 0;
	columns = -1;
	while (++columns < data->columns)
	{
		column_display(data, columns, w.ws_col, (extra ? 1 : 0));
		if (extra)
			--extra;
	}
	return (0);
}
