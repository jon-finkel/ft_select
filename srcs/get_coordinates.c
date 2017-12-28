/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 17:10:30 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/28 23:26:59 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void			get_coordinates(t_data *data)
{
	int		diff;

	if (data->extra && data->pos < data->extra * (data->rows + 1))
		data->curr_column = data->pos / (data->rows + 1);
	else
		data->curr_column = (data->pos - data->extra) / data->rows;
	data->x = data->padding * (data->curr_column + 1);
	data->x += data->curr_column * data->width + 2;
	if (!data->extra)
		diff = data->curr_column * data->rows;
	else
	{
		if (data->curr_column < data->extra)
			diff = data->curr_column * (data->rows + 1);
		else
		{
			diff = data->extra * (data->rows + 1);
			diff += (data->curr_column - data->extra) * data->rows;
		}
	}
	data->y = data->pos - diff + 2;
}
