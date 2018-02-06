/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 09:12:35 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/06 15:11:05 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void			display_border(char *move, const int fd, int nb,
					unsigned short ws_col)
{
	char		*str;
	int			k;
	wchar_t		hor_line[ws_col];

	IMOUTTAHERE(str = tgoto(move, 0, 0));
	ft_dprintf(fd, "%s%C", str, 0x256D);
	IMOUTTAHERE(str = tgoto(move, 0, nb + 5));
	ft_dprintf(fd, "%s%C", str, 0x2570);
	IMOUTTAHERE(str = tgoto(move, ws_col, 0));
	ft_dprintf(fd, "%s%C", str, 0x256E);
	IMOUTTAHERE(str = tgoto(move, ws_col, nb + 5));
	ft_dprintf(fd, "%s%C", str, 0x256F);
	k = -1;
	while (++k < ws_col - 1)
		hor_line[k] = 0x2500;
	hor_line[k] = L'\0';
	IMOUTTAHERE(str = tgoto(move, 1, 0));
	ft_dprintf(fd, "%s%S", str, hor_line);
	IMOUTTAHERE(str = tgoto(move, 1, nb + 5));
	ft_dprintf(fd, "%s%S", str, hor_line);
	IMOUTTAHERE(str = tgoto(move, ws_col - 28, nb + 5));
	ft_dprintf(fd, "%s {H}Press TAB to dismiss help{eoc} ", str);
}

static void			display_text2(char *move, const int fd,
					unsigned short ws_col)
{
	char		*str;
	int			x;

	x = (ws_col - (ws_col < 61 ? 11 : 56)) / 2;
	IMOUTTAHERE(str = tgoto(move, x, 0));
	if (ws_col < 61)
		ft_dprintf(fd, "%s {1c}ft_select{eoc} ", str);
	else
		ft_dprintf(fd, "%s {1c}ft_select - an interactive file selector"\
			", by {1b}Jon Finkel{eoc} ", str);
}

static void			display_text1(char *move, const int fd, int nb,
					unsigned short ws_col)
{
	char		*str;

	nb = nb / 2 - 2;
	IMOUTTAHERE(str = tgoto(move, (ws_col / 2) - 17, ++nb));
	ft_dprintf(fd, "%s{17H} -------------------------------- {eoc}\n", str);
	IMOUTTAHERE(str = tgoto(move, (ws_col / 2) - 17, ++nb));
	ft_dprintf(fd, "%s{17H} | SPACE : select/unselect file | {eoc}\n", str);
	IMOUTTAHERE(str = tgoto(move, (ws_col / 2) - 17, ++nb));
	ft_dprintf(fd, "%s{17H} | BACKSPACE :    unselect file | {eoc}\n", str);
	IMOUTTAHERE(str = tgoto(move, (ws_col / 2) - 17, ++nb));
	ft_dprintf(fd, "%s{17H} | * :               select all | {eoc}\n", str);
	IMOUTTAHERE(str = tgoto(move, (ws_col / 2) - 17, ++nb));
	ft_dprintf(fd, "%s{17H} | \\ :             unselect all | {eoc}\n", str);
	IMOUTTAHERE(str = tgoto(move, (ws_col / 2) - 17, ++nb));
	ft_dprintf(fd, "%s{17H} | ESCAPE :                exit | {eoc}\n", str);
	IMOUTTAHERE(str = tgoto(move, (ws_col / 2) - 17, ++nb));
	ft_dprintf(fd, "%s{17H} | %C%C%C%C:            move cursor | {eoc}\n", str,\
		0x2190, 0x2191, 0x2192, 0x2193);
	IMOUTTAHERE(str = tgoto(move, (ws_col / 2) - 17, ++nb));
	ft_dprintf(fd, "%s{17H} -------------------------------- {eoc}\n", str);
	display_text2(move, fd, ws_col);
}

int					display_help(t_data *data, unsigned short ws_col)
{
	char				*move;
	char				*str;
	int					nb;

	FAILZ(str = tgetstr("cl", NULL), -1);
	ft_putstr_fd(str, data->fd);
	nb = data->rows + (data->extra ? 1 : 0);
	if (nb < 10)
		nb = 6;
	FAILZ(move = tgetstr("cm", NULL), -1);
	display_border(move, data->fd, nb, ws_col);
	display_text1(move, data->fd, nb, ws_col);
	KTHXBYE;
}
