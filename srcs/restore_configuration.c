/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_configuration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:47:09 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/28 21:23:13 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			restore_configuration(t_data *data, t_flag flag)
{
	char		*str;

	PROTECT(str = tgetstr("ve", NULL), -1);
	ft_putstr_fd(str, data->fd);
	ft_putstr_fd("\033[?1049l", data->fd);
	close(data->fd);
	free(data->select);
	free(data);
	if (flag == E_EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	else if (flag == E_EXIT_FAILURE)
		exit(EXIT_FAILURE);
	return (0);
}
