/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:43:32 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/29 17:02:47 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

t_data				*g_data;

static int			initialize_termios(t_data *data)
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
	PROTECT(str = tgetstr("vi", NULL), -1);
	ft_putstr_fd(str, data->fd);
	return (0);
}

int					main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	if (argc == 1)
		ft_kill("usage: ft_select: argument1 [argument2 ...]");
	PROTECT(g_data = (t_data *)malloc(sizeof(t_data)), -1);
	PROTECT(g_data->argv = (char **)malloc(sizeof(char *) * argc), -1);
	PROTECT(g_data->select = (t_bool *)malloc(sizeof(t_bool) * (argc - 1)), -1);
	g_data->fd = open("/dev/tty", O_RDWR);
	NEG_PROTECT(initialize_termios(g_data), -1);
	ft_putstr_fd("\033[?1049h", g_data->fd);
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
	return (loop(g_data));
}
