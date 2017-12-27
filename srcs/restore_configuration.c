/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_configuration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:47:09 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/27 16:10:58 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			restore_configuration(t_data *data)
{
	char		*str;

	ft_cleanup(2, E_APTR, data->argv);
	free(data);
	PROTECT(str = tgetstr("ve", NULL), -1);
	ft_putstr(str);
	ft_putstr("\033[?1049h");
	return (0);
}
