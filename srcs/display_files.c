/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 18:28:37 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/26 23:45:13 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void			display_frame(char *move, int nb, unsigned short ws_col)
{
	char		*str;
	int			k;
	wchar_t		hor_line[ws_col];

	EXIT_PROTECT(str = tgetstr("cl", NULL));
	ft_putstr_fd(str, STDOUT_FILENO);
	EXIT_PROTECT(str = tgoto(move, 0, 0));
	ft_dprintf(STDOUT_FILENO, "%s%C", str, 0x256D);
	EXIT_PROTECT(str = tgoto(move, 0, nb + 3));
	ft_dprintf(STDOUT_FILENO, "%s%C", str, 0x2570);
	EXIT_PROTECT(str = tgoto(move, ws_col, 0));
	ft_dprintf(STDOUT_FILENO, "%s%C", str, 0x256E);
	EXIT_PROTECT(str = tgoto(move, ws_col, nb + 3));
	ft_dprintf(STDOUT_FILENO, "%s%C", str, 0x256F);
	k = -1;
	while (++k < ws_col - 1)
		hor_line[k] = 0x2500;
	hor_line[k] = L'\0';
	EXIT_PROTECT(str = tgoto(move, 1, 0));
	ft_dprintf(STDOUT_FILENO, "%s%S", str, hor_line);
	EXIT_PROTECT(str = tgoto(move, (ws_col - 56) / 2, 0));
	ft_dprintf(STDOUT_FILENO, "%s {1c}ft_select - an interactive file selector"\
		", by {1b}Jon Finkel{eoc} ", str);
	EXIT_PROTECT(str = tgoto(move, 1, nb + 3));
	ft_dprintf(STDOUT_FILENO, "%s%S", str, hor_line);
}

static void			column_display(t_data *data, int column, unsigned short col,
					short extra)
{
	char		*move;
	char		*str;
	int			x;
	int			y;

	EXIT_PROTECT(move = tgetstr("cm", NULL));
	x = (col - (data->width + 1) * data->columns) / (data->columns + 1);
	x = 2 + (column * (data->width + 1)) + (x * (column + 1));
	y = 2;
	column = -1;
	while (++column < data->rows + extra)
	{
		EXIT_PROTECT(str = tgoto(move, x, y++));
		ft_dprintf(STDOUT_FILENO, "%s%s", str, data->argv[data->argc++]);
	}
}

int					display_files(t_data *data)
{
	char				*move;
	char				*str;
	int					columns;
	short				extra;
	struct winsize		w;

	NEG_PROTECT(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w), -1);
	--w.ws_col;
	PROTECT(move = tgetstr("cm", NULL), -1);
	data->columns = (w.ws_col - 4) / (data->width + 1);
	data->rows = data->argc / data->columns;
	extra = data->argc % data->columns;
	display_frame(move, data->rows + (extra ? 1 : 0), w.ws_col);
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
