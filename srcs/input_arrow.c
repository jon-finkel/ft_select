/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 12:06:55 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/28 23:29:15 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int			move_cursor_up(t_data *data)
{
	NEG_PROTECT(color_output(data), -1);
	if (!data->pos)
		data->pos = data->argc - 1;
	else
		--data->pos;
	get_coordinates(data);
	return (0);
}

static int			move_cursor_down(t_data *data)
{
	NEG_PROTECT(color_output(data), -1);
	if (data->pos == data->argc - 1)
		data->pos = 0;
	else
		++data->pos;
	get_coordinates(data);
	return (0);
}

static int			move_cursor_right(t_data *data)
{
	NEG_PROTECT(color_output(data), -1);
	if ((data->extra - 1 == data->curr_column && data->y - 2 == data->rows)
		|| (!data->extra && data->pos == data->argc - 1))
		data->pos = 0;
	else if (data->curr_column == data->columns - 1)
		data->pos = data->y - 1;
	else
		data->pos += data->rows + (data->curr_column < data->extra ? 1 : 0);
	get_coordinates(data);
	return (0);
}

static int			move_cursor_left(t_data *data)
{
	NEG_PROTECT(color_output(data), -1);
	if (!data->pos && !data->extra)
		move_cursor_up(data);
	else if (!data->pos && data->extra)
		data->pos = data->extra * (data->rows + (data->extra ? 1 : 0)) - 1;
	else if (data->x == data->padding + 2)
		data->pos = data->argc - 1 - ((data->rows + 2) - data->y);
	else
	{
		--data->curr_column;
		data->pos -= data->rows + (data->curr_column < data->extra ? 1 : 0);
	}
	get_coordinates(data);
	return (0);
}

int					input_arrow(t_data *data, const char *const buff)
{
	if (ft_strnequ(buff, "\033[", 2))
	{
		if (buff[2] == 'A')
			move_cursor_up(data);
		else if (buff[2] == 'B')
			move_cursor_down(data);
		else if (buff[2] == 'C')
			move_cursor_right(data);
		else if (buff[2] == 'D')
			move_cursor_left(data);
		flag_underline(E_ENABLE, data->fd);
		NEG_PROTECT(color_output(data), -1);
		flag_underline(E_DISABLE, data->fd);
	}
	return (0);
}
