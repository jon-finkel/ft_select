/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_configuration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:47:09 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/28 14:22:45 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			restore_configuration(t_data *data)
{
	char		*str;

	ft_cleanup(4, E_PTR, data->select, E_APTR, data->argv);
	PROTECT(str = tgetstr("ve", NULL), -1);
	ft_putstr(str);
	ft_putstr("\033[?1049h");
	free(data);
	return (0);
}
