/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 17:24:29 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/10 20:27:58 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void			signal_handler(int signo)
{
	extern t_data		*g_data;

	if (signo == SIGINT || signo == SIGQUIT || signo == SIGTERM)
		restore_config(g_data, E_EXIT_SUCCESS);
	else if (signo == SIGCONT)
	{
		ft_memdel((void **)&g_data->oldcc);
		initialize_termios(g_data);
	}
	else if (signo == SIGTSTP)
		restore_config(g_data, E_SUSPEND);
	else if (signo == SIGWINCH)
		check_window_size(g_data);
}
