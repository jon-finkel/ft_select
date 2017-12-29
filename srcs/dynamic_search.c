/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 15:27:25 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/29 15:35:35 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int			find_file(t_data *data, const char *move, const char *file)
{
	char		*str;
	int			k;
	int			p;

	k = 0;
	while (++k < data->width - 1)
	{
		p = -1;
		while (++p < data->argc)
			if (ft_strnequ(data->argv[p], file, k))
			{
				data->pos = p;
				get_coordinates(data);
				color_output(data);
				k = INT_MAX - 1;
				break ;
			}
	}
	if (k == INT_MAX)
		return (0);
	PROTECT(str = tgoto(move, 0, data->rows + (data->extra ? 5 : 4)), -1);
	ft_putstr_fd(str, data->fd);
	PROTECT(str = tgetstr("cd", NULL), -1);
	ft_dprintf(data->fd, "%s  {1G}FILE NOT FOUND !{eoc}", str);
	return (0);
}

int					dynamic_search(t_data *data, char *file, const char buff,
					int *x)
{
	char				*move;
	char				*str;

	if (!x && (buff == '\010' || buff == '\177'))
		return (0);
	else if (buff == '\010' || buff == '\177')
		*x -= 1;
	else
		file[++(*x) - 1] = buff;
	file[*x] = '\0';
	PROTECT(move = tgetstr("cm", NULL), -1);
	PROTECT(str = tgoto(move, 0, data->rows + (data->extra ? 5 : 4)), -1);
	ft_putstr_fd(str, data->fd);
	PROTECT(str = tgetstr("cd", NULL), -1);
	ft_dprintf(data->fd, "%s{17H}  search file: %s{eoc}", str, file);
	NEG_PROTECT(find_file(data, move, file), -1);
	return (0);
}
