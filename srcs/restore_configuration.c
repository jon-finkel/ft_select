/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_configuration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:47:09 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/29 19:20:24 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int			restore_termios(t_data *data)
{
//	char				buffer[2048];
	char				*str;
//	char				*termtype;
//	struct termios		term;

//	PROTECT(termtype = getenv("TERM"), -1);
//	NEG_PROTECT(tgetent(buffer, termtype), -1);
//	NEG_PROTECT(tcgetattr(STDIN_FILENO, &term), -1);
//	term.c_lflag |= ICANON;
//	term.c_cc[VMIN] = 1;
//	term.c_cc[VTIME] = 0;
//	NEG_PROTECT(tcsetattr(STDIN_FILENO, TCSADRAIN, &term), -1);
	PROTECT(str = tgetstr("ve", NULL), -1);
	ft_putstr_fd(str, data->fd);
	return (0);
}

int					restore_configuration(t_data *data, t_flag flag)
{
	restore_termios(data);
	ft_putstr_fd("\033[?1049l", data->fd);
	if (flag == E_OUTPUT)
		ft_putstr_fd(data->string, STDOUT_FILENO);
	if (flag != E_SUSPEND)
	{
		close(data->fd);
		ft_strdel(&data->string);
		ft_cleanup(4, E_APTR, data->argv, E_PTR, data->select);
	}
	if (flag == E_EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	else if (flag == E_EXIT_FAILURE)
		exit(EXIT_FAILURE);
	return (0);
}
