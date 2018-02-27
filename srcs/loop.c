/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:03:16 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/26 21:42:25 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int			remove_element(t_data *data, int *nb)
{
	bool		space;
	char		buff[MAXPATHLEN + 1024];
	int			k;

	*nb -= 1;
	data->select[data->pos] = false;
	ft_strdel(&data->string);
	if (*nb > 0)
	{
		data->string = ft_strnew(0);
		space = false;
		k = -1;
		while (++k < data->argc)
			if (data->select[k] == true)
			{
				ft_memset(buff, '\0', MAXPATHLEN + 1024);
				if (space == true)
					ft_strcat(buff, " ");
				ft_strcat(buff, data->argv[k]);
				data->string = ft_strjoin(data->string, buff, true);
				space = true;
			}
	}
	KTHXBYE;
}

static int			toggle_elem(t_data *data, int *nb)
{
	char		buff[MAXPATHLEN + 1024];

	ft_memset(buff, '\0', MAXPATHLEN + 1024);
	if (data->select[data->pos] == true)
		remove_element(data, nb);
	else
	{
		*nb += 1;
		if (*nb == 1)
			data->string = ft_strdup(data->argv[data->pos]);
		else
		{
			ft_strcat(buff, " ");
			ft_strcat(buff, data->argv[data->pos]);
			data->string = ft_strjoin(data->string, buff, true);
		}
		data->select[data->pos] = true;
	}
	flag_underline(E_ENABLE, data->fd);
	color_output(data, data->pos, data->x, data->y);
	flag_underline(E_DISABLE, data->fd);
	input_arrow(data, "\033[B");
	KTHXBYE;
}

static int			delete_element(t_data *data, int *nb)
{
	int		k;

	if (data->select[data->pos] == true)
		remove_element(data, nb);
	k = data->pos;
	while (data->argv[++k])
	{
		data->argv[k - 1] = data->argv[k];
		data->select[k - 1] = data->select[k];
	}
	data->argv[k] = NULL;
	--data->argc;
	if (!data->argc)
		restore_config(data, E_EXIT_SUCCESS);
	if (data->pos)
		--data->pos;
	check_window_size(data);
	KTHXBYE;
}

static int			full_toggle(t_data *data, int *nb, t_flag flag, int k)
{
	char		buff[1024];

	ft_strdel(&data->string);
	if (flag == E_DISABLE && !(data->pos = 0))
	{
		*nb = 0;
		while (++k < data->argc)
			data->select[k] = false;
	}
	else
	{
		data->string = ft_strdup(data->argv[++k]);
		while (++k < data->argc)
		{
			data->select[k] = true;
			ft_memset(buff, '\0', 1024);
			ft_strcat(buff, " ");
			ft_strcat(buff, data->argv[k]);
			data->string = ft_strjoin(data->string, buff, true);
		}
		data->select[0] = true;
		*nb = k;
	}
	check_window_size(data);
	KTHXBYE;
}

int					loop(t_data *data)
{
	char			buff[5];
	static int		nb = 0;

	while (101010)
	{
		ft_memset(buff, '\0', 5);
		read(STDIN_FILENO, buff, 4);
		if (*buff == 127 || ft_strnequ(buff, "\033[3~", 4))
			delete_element(data, &nb);
		else if ((*buff == 9 && toggle_help(data) == -1) || *buff == 10)
			NOMOAR;
		else if (ft_strequ(buff, "\033") || (ft_strnequ(buff, "\033", 1)
			&& input_arrow(data, buff) == -1))
			NOMOAR;
		else if ((*buff == 42 && full_toggle(data, &nb, E_ENABLE, -1) == -1)
			|| (*buff == 92 && full_toggle(data, &nb, E_DISABLE, -1) == -1))
			NOMOAR;
		else if (lettercheck(*buff) && dynamic_search(data, buff, 0) == -1)
			NOMOAR;
		else if ((*buff == 10 || *buff == 32) && toggle_elem(data, &nb) == -1)
			NOMOAR;
	}
	GIMME(restore_config(data, (*buff == 10 ? E_OUTPUT : E_EXIT_SUCCESS)));
}
