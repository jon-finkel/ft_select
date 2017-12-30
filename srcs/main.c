/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:43:32 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/29 19:19:19 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

t_data		*g_data;

int			main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	if (argc == 1)
		ft_kill("usage: ft_select: argument1 [argument2 ...]");
	PROTECT(g_data = (t_data *)malloc(sizeof(t_data)), -1);
	PROTECT(g_data->argv = (char **)malloc(sizeof(char *) * argc), -1);
	PROTECT(g_data->select = (t_bool *)malloc(sizeof(t_bool) * (argc - 1)), -1);
	g_data->fd = open("/dev/tty", O_RDWR);
	g_data->argv[g_data->argc] = NULL;
	g_data->argc = argc - 1;
	g_data->pos = 0;
	g_data->curr_column = 0;
	g_data->width = 0;
	g_data->status = E_REGULAR;
	while (--argc)
	{
		PROTECT(g_data->argv[argc - 1] = ft_strdup(argv[argc]), -1);
		g_data->width = _MAX(g_data->width, ft_strlen(argv[argc]));
		g_data->select[g_data->argc] = FALSE;
	}
	++g_data->width;
	ft_interceptor(&signal_handler, 5, SIGINT, SIGQUIT, SIGTERM, SIGTSTP,\
		SIGCONT, SIGWINCH);
	return (initialize_termios(g_data));
}
