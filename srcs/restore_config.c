/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 10:17:22 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/10 22:55:48 by nfinkel          ###   ########.fr       */
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
		ioctl(data->fd, TIOCSTI, buff);
	}
	tcsetattr(data->fd, TCSANOW, data->oldcc);
	ft_memdel((void **)&data->oldcc);
	str = tgetstr("ve", NULL);
	ft_putstr_fd(str, data->fd);
	KTHXBYE;
}

int					restore_config(t_data *data, t_flag flag)
{
	restore_termios(data, flag);
	ft_putstr_fd("\033[?1049l", data->fd);
	if (flag == E_OUTPUT && data->string)
		ft_putendl_fd(data->string, STDOUT_FILENO);
	if (flag != E_SUSPEND)
		close(data->fd);
	if (flag == E_EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	else if (flag == E_EXIT_FAILURE)
		exit(EXIT_FAILURE);
	KTHXBYE;
}
