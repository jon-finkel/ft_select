/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Bnb: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:43:07 bnb nfinkel           #+#    #+#             */
/*   Updated: 2017/12/28 21:11:43 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void			display_border(char *move, const int fd, int nb,
					unsigned short ws_col)
{
	char		*str;
	int			k;
	wchar_t		hor_line[ws_col];

	EXIT_PROTECT(str = tgoto(move, 0, 0));
	ft_dprintf(fd, "%s%C", str, 0x256D);
	EXIT_PROTECT(str = tgoto(move, 0, nb + 3));
	ft_dprintf(fd, "%s%C", str, 0x2570);
	EXIT_PROTECT(str = tgoto(move, ws_col, 0));
	ft_dprintf(fd, "%s%C", str, 0x256E);
	EXIT_PROTECT(str = tgoto(move, ws_col, nb + 3));
	ft_dprintf(fd, "%s%C", str, 0x256F);
	k = -1;
	while (++k < ws_col - 1)
		hor_line[k] = 0x2500;
	hor_line[k] = L'\0';
	EXIT_PROTECT(str = tgoto(move, 1, 0));
	ft_dprintf(fd, "%s%S", str, hor_line);
	EXIT_PROTECT(str = tgoto(move, (ws_col - 56) / 2, 0));
	ft_dprintf(fd, "%s {1c}ft_select - an interactive file selector"\
		", by {1b}Jon Finkel{eoc} ", str);
	EXIT_PROTECT(str = tgoto(move, 1, nb + 3));
	ft_dprintf(fd, "%s%S", str, hor_line);
	EXIT_PROTECT(str = tgoto(move, ws_col - 28, nb + 3));
	ft_dprintf(fd, "%s {H}Press TAB to dismiss help{eoc} ", str);
}

static void			display_text(char *move, const int fd, int nb,
					unsigned short ws_col)
{
	char		*str;

	display_border(move, fd, nb, ws_col);
	nb = nb / 2 - 2;
	EXIT_PROTECT(str = tgoto(move, (ws_col / 2) - 18, ++nb));
	ft_dprintf(fd, "%s{17H} -------------------------------- {eoc}\n", str);
	EXIT_PROTECT(str = tgoto(move, (ws_col / 2) - 18, ++nb));
	ft_dprintf(fd, "%s{17H} | SPACE : select/deselect file | {eoc}\n", str);
	EXIT_PROTECT(str = tgoto(move, (ws_col / 2) - 18, ++nb));
	ft_dprintf(fd, "%s{17H} | BACKSPACE :    deselect file | {eoc}\n", str);
	EXIT_PROTECT(str = tgoto(move, (ws_col / 2) - 18, ++nb));
	ft_dprintf(fd, "%s{17H} | ESCAPE :                exit | {eoc}\n", str);
	EXIT_PROTECT(str = tgoto(move, (ws_col / 2) - 18, ++nb));
	ft_dprintf(fd, "%s{17H} | %C%C%C%C:            move cursor | {eoc}\n", str,\
		0x2190, 0x2191, 0x2192, 0x2193);
	EXIT_PROTECT(str = tgoto(move, (ws_col / 2) - 18, ++nb));
	ft_dprintf(fd, "%s{17H} -------------------------------- {eoc}\n", str);
}

int			display_help(t_data *data)
{
	char				*move;
	char				*str;
	int					nb;
	struct winsize		w;

	NEG_PROTECT(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w), -1);
	--w.ws_col;
	PROTECT(str = tgetstr("cl", NULL), -1);
	ft_putstr_fd(str, data->fd);
	nb = data->rows + (data->extra ? 1 : 0);
	if (nb < 10)
		nb = 6;
	PROTECT(move = tgetstr("cm", NULL), -1);
	display_text(move, data->fd, nb, w.ws_col);
	return (0);
}
