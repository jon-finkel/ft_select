/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 10:17:22 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/06 15:24:19 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int			restore_termios(t_data *data, t_flag flag)
{
	char		buff[2];
	char		*str;

	if (flag == E_SUSPEND)
	{
		buff[0] = data->oldcc->c_cc[VSUSP];
		buff[1] = '\0';
		EPICFAILZ(ioctl(data->fd, TIOCSTI, buff), -1);
	}
	EPICFAILZ(tcsetattr(data->fd, TCSANOW, data->oldcc), -1);
	ft_memdel((void **)&data->oldcc);
	FAILZ(str = tgetstr("ve", NULL), -1);
	ft_putstr_fd(str, data->fd);
	KTHXBYE;
}

int					restore_config(t_data *data, t_flag flag)
{
	EPICFAILZ(restore_termios(data, flag), -1);
	ft_putstr_fd("\033[?1049l", data->fd);
	if (flag == E_OUTPUT)
		ft_putendl_fd(data->string, STDOUT_FILENO);
	if (flag != E_SUSPEND)
		close(data->fd);
	if (flag == E_EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	else if (flag == E_EXIT_FAILURE)
		exit(EXIT_FAILURE);
	KTHXBYE;
}
