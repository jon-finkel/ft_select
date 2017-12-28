/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 18:28:37 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/28 21:48:48 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int			display_text(t_data *data, char *move, int nb,
					unsigned short ws_col)
{
	char		*str;
	int			k;
	wchar_t		hor_line[ws_col];

	k = -1;
	while (++k < ws_col - 1)
		hor_line[k] = 0x2500;
	hor_line[k] = L'\0';
	PROTECT(str = tgoto(move, 1, 0), -1);
	ft_dprintf(data->fd, "%s%S", str, hor_line);
	PROTECT(str = tgoto(move, (ws_col - 56) / 2, 0), -1);
	ft_dprintf(data->fd, "%s {1c}ft_select - an interactive file selector"\
		", by {1b}Jon Finkel{eoc} ", str);
	PROTECT(str = tgoto(move, 1, nb + 3), -1);
	ft_dprintf(data->fd, "%s%S", str, hor_line);
	PROTECT(str = tgoto(move, ws_col - 21, nb + 3), -1);
	ft_dprintf(data->fd, "%s {H}Press TAB for help{eoc} ", str);
	return (0);
}

static int			display_frame(t_data *data, unsigned short ws_col)
{
	char		*move;
	char		*str;
	int			nb;

	nb = data->rows + (data->extra ? 1 : 0);
	PROTECT(str = tgetstr("cl", NULL), -1);
	ft_putstr_fd(str, data->fd);
	PROTECT(move = tgetstr("cm", NULL), -1);
	PROTECT(str = tgoto(move, 0, 0), -1);
	ft_dprintf(data->fd, "%s%C", str, 0x256D);
	PROTECT(str = tgoto(move, 0, nb + 3), -1);
	ft_dprintf(data->fd, "%s%C", str, 0x2570);
	PROTECT(str = tgoto(move, ws_col, 0), -1);
	ft_dprintf(data->fd, "%s%C", str, 0x256E);
	PROTECT(str = tgoto(move, ws_col, nb + 3), -1);
	ft_dprintf(data->fd, "%s%C", str, 0x256F);
	display_text(data, move, nb, ws_col);
	return (0);
}

static int			color_display(t_data *data, const char *move, const int fd)
{
	char			*file;
	char			*path;
	struct stat		w_stat;

	PROTECT(path = ft_strnew(MAXPATHLEN), -1);
	PROTECT(path = getcwd(path, MAXPATHLEN), -1);
	NEG_PROTECT(ft_asprintf(&file, "%s/%s", path, data->argv[data->argc]), -1);
	NEG_PROTECT(stat(file, &w_stat), -1);
	ft_cleanup(4, E_PTR, file, E_PTR, path);
	if (data->select[data->argc] == TRUE)
		flag_reverse_video(E_ENABLE, fd);
	if (S_ISDIR(w_stat.st_mode))
		ft_dprintf(fd, "%s{1Gx}%s{eoc}", move, data->argv[data->argc]);
	else if (w_stat.st_mode & S_IXUSR)
		ft_dprintf(fd, "%s{Dx}%s{eoc}", move, data->argv[data->argc]);
	else
		ft_dprintf(fd, "%s%s", move, data->argv[data->argc]);
	if (data->select[data->argc] == TRUE)
		flag_reverse_video(E_DISABLE, fd);
	return (0);
}

static int			column_display(t_data *data, int column, short extra)
{
	char		*move;
	char		*str;
	int			x;
	int			y;

	PROTECT(move = tgetstr("cm", NULL), -1);
	x = column * data->width + data->padding * (column + 1) + 2;
	y = 1;
	column = -1;
	while (++column < data->rows + extra)
	{
		if (data->argc == data->pos)
			flag_underline(E_ENABLE, data->fd);
		PROTECT(str = tgoto(move, x, ++y), -1);
		NEG_PROTECT(color_display(data, str, data->fd), -1);
		if (data->argc == data->pos)
			flag_underline(E_DISABLE, data->fd);
		++data->argc;
	}
	return (0);
}

int					display_files(t_data *data)
{
	int					columns;
	short				extra;
	struct winsize		w;

	NEG_PROTECT(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w), -1);
	--w.ws_col;
	data->columns = (w.ws_col - 4) / data->width;
	data->rows = data->argc / data->columns;
	data->extra = data->argc % data->columns;
	data->padding = w.ws_col - data->width * data->columns;
	data->padding /= data->columns + 1;
	data->argc = 0;
	extra = data->extra;
	NEG_PROTECT(display_frame(data, w.ws_col), -1);
	get_coordinates(data);
	columns = -1;
	while (++columns < data->columns)
	{
		NEG_PROTECT(column_display(data, columns, (extra ? 1 : 0)), -1);
		if (extra)
			--extra;
	}
	return (0);
}
