/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:43:32 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/10 23:04:31 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

t_data		*g_data;

static void			set_signals(void)
{
	struct sigaction		s;

	s.sa_handler = signal_handler;
	s.sa_mask = 0;
	s.sa_flags = 0;
	sigaction(SIGINT, &s, NULL);
	sigaction(SIGQUIT, &s, NULL);
	sigaction(SIGTERM, &s, NULL);
	s.sa_flags = SA_RESTART;
	sigaction(SIGWINCH, &s, NULL);
}

void				get_width(t_data *data)
{
	int		argc;

	argc = data->argc;
	while (--argc)
		data->width = MAX(data->width, ft_strlen(data->argv[argc]) + 1);
}

int					main(int argc, const char *argv[])
{
	if (argc == 1)
	{
		ft_putendl("usage: ft_select: argument1 [argument2 ...]");
		KTHXBYE;
	}
	setlocale(LC_ALL, "");
	g_data = (t_data *)ft_memalloc(sizeof(t_data));
	g_data->select = (bool *)ft_memalloc(sizeof(bool) * (argc - 1));
	if (!isatty(STDIN_FILENO))
		ft_fatal("unsupported device");
	if (isatty(g_data->fd = open("/dev/tty", O_RDWR)) == false)
		ft_fatal("not a terminal type device");
	g_data->argv = (char **)argv + 1;
	g_data->argc = argc - 1;
	g_data->width = 1;
	g_data->status = E_REGULAR;
	get_width(g_data);
	set_signals();
	GIMME(initialize_termios(g_data));
}
