/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:43:32 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/31 17:38:45 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

t_data		*g_data;

static void			set_signals(void)
{
	struct sigaction		s;

	s.__sigaction_u.__sa_handler = &signal_handler;
	s.sa_flags = 0;
	s.sa_mask = 0;
	sigaction(SIGINT, &s, NULL);
	sigaction(SIGQUIT, &s, NULL);
	sigaction(SIGTERM, &s, NULL);
	sigaction(SIGCONT, &s, NULL);
	sigaction(SIGTSTP, &s, NULL);
	s.sa_flags = SA_RESTART;
	sigaction(SIGWINCH, &s, NULL);
}

int					main(int argc, char *argv[])
{
	if (argc == 1)
	{
		ft_putstr("usage: ft_select: argument1 [argument2 ...]");
		return (0);
	}
	setlocale(LC_ALL, "");
	PROTECT(g_data = (t_data *)malloc(sizeof(t_data)), -1);
	PROTECT(g_data->select = (t_bool *)malloc(sizeof(t_bool) * (argc - 1)), -1);
	if (isatty(g_data->fd = open("/dev/tty", O_RDWR)) == FALSE)
		ft_fatal("not a terminal type device");
	g_data->string = NULL;
	g_data->oldcc = NULL;
	g_data->argv = argv + 1;
	g_data->argc = argc - 1;
	g_data->pos = 0;
	g_data->curr_column = 0;
	g_data->width = 1;
	g_data->status = E_REGULAR;
	while (--argc)
	{
		g_data->width = _MAX(g_data->width, ft_strlen(argv[argc]) + 1);
		g_data->select[argc - 1] = FALSE;
	}
	set_signals();
	return (initialize_termios(g_data));
}
