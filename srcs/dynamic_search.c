/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 15:27:25 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/31 09:29:18 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int			find_file(t_data *data, const char *move, const char *file)
{
	char		*str;
	int			k;

	k = -1;
	while (++k < data->argc)
		if (ft_strnequ(file, data->argv[k], ft_strlen(file)))
		{
			NEG_PROTECT(color_output(data, data->pos, data->x, data->y), -1);
			data->pos = k;
			get_coordinates(data);
			flag_underline(E_ENABLE, data->fd);
			NEG_PROTECT(color_output(data, data->pos, data->x, data->y), -1);
			flag_underline(E_DISABLE, data->fd);
			return (0);
		}
	PROTECT(str = tgoto(move, 2, data->rows + (data->extra ? 6 : 5)), -1);
	ft_dprintf(data->fd, "%sFILE NOT FOUND !", str);
	return (0);
}

static int			search_letter(t_data *data, char *file, const char buff,
					int *x)
{
	char				*move;
	char				*str;

	if ((!*x && (buff == '\010' || buff == '\177')) || buff == '\012')
		return (255);
	else if (buff == '\010' || buff == '\177')
		*x -= 1;
	else
		file[++(*x) - 1] = buff;
	file[*x] = '\0';
	PROTECT(move = tgetstr("cm", NULL), -1);
	PROTECT(str = tgoto(move, 2, data->rows + (data->extra ? 5 : 4)), -1);
	ft_putstr_fd(str, data->fd);
	PROTECT(str = tgetstr("cd", NULL), -1);
	ft_dprintf(data->fd, "%s{17H}search file: %s{eoc}", str, file);
	NEG_PROTECT(find_file(data, move, file), -1);
	return (0);
}

int					dynamic_search(t_data *data, char *buff, int x)
{
	char		file[512];
	int			ret;

	ret = 0;
	while (101010)
	{
		if (ft_strequ(buff, "\033") || ft_strequ(buff, "\040"))
			break ;
		else if (ft_strequ(buff, "\011"))
			return (toggle_help(data));
		else if (*buff == '\033' && (ret = input_arrow(data, buff)) < INT_MAX)
			break ;
		else if ((ret = search_letter(data, file, *buff, &x)) == -1
			|| ret == 255)
				break ;
		ft_memset(buff, '\0', 4);
		NEG_PROTECT(read(STDIN_FILENO, buff, 3), -1);
	}
	NEG_PROTECT(check_window_size(data), -1);
	return (ret);
}
