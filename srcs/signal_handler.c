/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 17:24:29 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/31 12:16:49 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void			signal_handler(int signo)
{
	extern t_data			*g_data;

	if (signo == SIGINT || signo == SIGQUIT || signo == SIGTERM)
		restore_config(g_data, E_EXIT_SUCCESS);
	else if (signo == SIGCONT)
		initialize_termios(g_data);
	else if (signo == SIGTSTP)
		restore_config(g_data, E_SUSPEND);
	else if (signo == SIGWINCH)
		if (check_window_size(g_data) == -1)
			restore_config(g_data, E_EXIT_FAILURE);
}
