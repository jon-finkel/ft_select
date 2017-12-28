/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 17:24:29 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/28 20:01:04 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int			check_window_size(t_data *data)
{
	if (data->status == E_HELP)
		NEG_PROTECT(display_help(data), -1);
	else
		NEG_PROTECT(display_files(data), -1);
//	if (data->status == E_DYNAMIC)
//		NEG_PROTECT(, -1);
	return (0);
}

void			signal_handler(int signo)
{
	extern t_data		*g_data;

	if (signo == SIGINT)
		restore_configuration(g_data, E_EXIT_SUCCESS);
	else if (signo == SIGWINCH)
		if (check_window_size(g_data) == -1)
			restore_configuration(g_data, E_EXIT_FAILURE);
}
