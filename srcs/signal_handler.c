/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 17:24:29 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/28 14:24:12 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void			signal_handler(int signo)
{
	extern t_data		*g_data;

	if (signo == SIGINT)
	{
		restore_configuration(g_data);
		exit(EXIT_SUCCESS);
	}
	else if (signo == SIGWINCH && display_files(g_data) == -1)
	{
		restore_configuration(g_data);
		exit(EXIT_FAILURE);
	}
}
