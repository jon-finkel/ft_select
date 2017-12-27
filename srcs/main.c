/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:43:32 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/27 16:03:32 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

t_data					*g_data;

static int				initialize_termios(void)
{
	char				buffer[2048];
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
	return (0);
}

static t_data			*initialize_data(char **argv, int argc)
{
	t_data		*data;

	PROTECT(data = (t_data *)malloc(sizeof(t_data)), NULL);
	PROTECT(data->argv = (char **)malloc(sizeof(char *) * argc), NULL);
	data->argc = argc - 1;
	data->argv[data->argc] = NULL;
	data->pos = 0;
	data->curr_column = 0;
	data->width = 0;
	while (--argc)
	{
		PROTECT(data->argv[argc - 1] = ft_strdup(argv[argc]), NULL);
		data->width = _MAX(data->width, ft_strlen(argv[argc]));
	}
	++data->width;
	return (data);
}

int						main(int argc, char *argv[])
{
	char		buff[4];

	setlocale(LC_ALL, "");
	if (argc == 1)
		ft_kill("usage: ft_select: argument1 [argument2 ...]");
	ft_putstr("\033[?1049l");
	NEG_PROTECT(initialize_termios(), -1);
	PROTECT(g_data = initialize_data(argv, argc), -1);
	NEG_PROTECT(display_files(g_data), -1);
	ft_interceptor(&signal_handler, 2, SIGINT, SIGWINCH);
	while (101010)
	{
		ft_memset(buff, '\0', 4);
		NEG_PROTECT(read(STDIN_FILENO, &buff, 3), -1);
		if (ft_strequ(buff, "\033") || input_key(g_data, buff) == -1)
			break ;
	}
	return (restore_configuration(g_data));
}
