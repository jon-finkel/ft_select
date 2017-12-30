/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_termios.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 18:23:56 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/29 19:13:44 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			initialize_termios(t_data *data)
{
	char				buffer[2048];
	char				*str;
	char				*termtype;
	int					ret;
	struct termios		term;

	if (!(termtype = getenv("TERM")))
		ft_kill("ft_select: specify a terminal type with `setenv TERM`");
	if (!(ret = tgetent(buffer, termtype)))
		ft_kill("ft_select: terminal type is not defined");
	NEG_PROTECT(ret, -1);
	NEG_PROTECT(tcgetattr(STDIN_FILENO, &term), -1);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	NEG_PROTECT(tcsetattr(STDIN_FILENO, TCSADRAIN, &term), -1);
	ft_putstr_fd("\033[?1049h", data->fd);
	PROTECT(str = tgetstr("vi", NULL), -1);
	ft_putstr_fd(str, data->fd);
	NEG_PROTECT(display_files(data), -1);
	return (loop(data));
}
