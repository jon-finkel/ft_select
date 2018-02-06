/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_termios.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 18:23:56 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/06 15:13:37 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void			set_signals(void)
{
	struct sigaction		s;

	s.sa_handler = &signal_handler;
	s.sa_mask = 0;
	s.sa_flags = 0;
	sigaction(SIGCONT, &s, NULL);
	s.sa_flags = SA_RESETHAND;
	sigaction(SIGTSTP, &s, NULL);
}

int					initialize_termios(t_data *data)
{
	char				*str;
	char				*termtype;
	struct termios		term;

	set_signals();
	if (!(termtype = getenv("TERM")))
		ft_fatal("specify a terminal type with `setenv TERM`");
	if (tgetent(NULL, termtype) < 1)
		ft_fatal("terminal type is not defined");
	EPICFAILZ(tcgetattr(data->fd, &term), -1);
	FAILZ(data->oldcc = (struct termios *)malloc(sizeof(struct termios)), -1);
	ft_memmove(data->oldcc, &term, sizeof(struct termios));
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	EPICFAILZ(tcsetattr(data->fd, TCSADRAIN, &term), -1);
	ft_putstr_fd("\033[?1049h", data->fd);
	FAILZ(str = tgetstr("vi", NULL), -1);
	ft_putstr_fd(str, data->fd);
	EPICFAILZ(check_window_size(data), -1);
	GIMME(loop(data));
}
