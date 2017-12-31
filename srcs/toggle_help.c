/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 09:32:45 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/31 09:33:00 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			toggle_help(t_data *data)
{
	char		buff[4];

	data->status = E_HELP;
	NEG_PROTECT(check_window_size(data), -1);
	while (101010)
	{
		ft_memset(buff, '\0', 4);
		NEG_PROTECT(read(STDIN_FILENO, &buff, 3), -1);
		if (ft_strequ(buff, "\033"))
			return (-1);
		else if (ft_strequ(buff, "\011"))
			break ;
	}
	data->status = E_REGULAR;
	NEG_PROTECT(check_window_size(data), -1);
	return (0);
}
