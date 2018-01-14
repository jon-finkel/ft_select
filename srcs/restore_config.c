/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 10:17:22 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/14 11:47:47 by nfinkel          ###   ########.fr       */
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
		NEG_PROTECT(ioctl(data->fd, TIOCSTI, buff), -1);
	}
	NEG_PROTECT(tcsetattr(data->fd, TCSANOW, data->oldcc), -1);
	ft_memdel((void **)&data->oldcc);
	PROTECT(str = tgetstr("ve", NULL), -1);
	ft_putstr_fd(str, data->fd);
	return (0);
}

int					restore_config(t_data *data, t_flag flag)
{
	NEG_PROTECT(restore_termios(data, flag), -1);
	ft_putstr_fd("\033[?1049l", data->fd);
	if (flag == E_OUTPUT)
		ft_putendl_fd(data->string, STDOUT_FILENO);
	if (flag != E_SUSPEND)
		close(data->fd);
	if (flag == E_EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	else if (flag == E_EXIT_FAILURE)
		exit(EXIT_FAILURE);
	return (0);
}
