/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 15:27:25 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/26 21:37:13 by nfinkel          ###   ########.fr       */
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
			color_output(data, data->pos, data->x, data->y);
			data->pos = k;
			get_coordinates(data);
			flag_underline(E_ENABLE, data->fd);
			color_output(data, data->pos, data->x, data->y);
			flag_underline(E_DISABLE, data->fd);
			KTHXBYE;
		}
	str = tgoto(move, 2, data->rows + (data->extra ? 6 : 5));
	ft_dprintf(data->fd, "%sFILE NOT FOUND !", str);
	KTHXBYE;
}

static int			search_letter(t_data *data, char *file, const char buff,
					int *x)
{
	char				*move;
	char				*str;

	if ((!*x && (buff == '\010' || buff == '\177')) || buff == '\012')
		GIMME(255);
	else if (buff == '\010' || buff == '\177')
		*x -= 1;
	else
		file[++(*x) - 1] = buff;
	file[*x] = '\0';
	move = tgetstr("cm", NULL);
	str = tgoto(move, 2, data->rows + (data->extra ? 5 : 4));
	ft_putstr_fd(str, data->fd);
	str = tgetstr("cd", NULL);
	ft_dprintf(data->fd, "%s{17H}search file: %s{eoc}", str, file);
	find_file(data, move, file);
	KTHXBYE;
}

int					dynamic_search(t_data *data, char *buff, int x)
{
	char		file[512];
	int			ret;

	ret = 0;
	while (101010)
	{
		if (ft_strequ(buff, "\033") || ft_strequ(buff, "\040"))
			NOMOAR;
		else if (ft_strequ(buff, "\011"))
			GIMME(toggle_help(data));
		else if (*buff == '\033' && (ret = input_arrow(data, buff)) < INT_MAX)
			NOMOAR;
		else if ((ret = search_letter(data, file, *buff, &x)) == -1
			|| ret == 255)
			NOMOAR;
		ft_memset(buff, '\0', 4);
		read(STDIN_FILENO, buff, 3);
	}
	check_window_size(data);
	GIMME(ret);
}
