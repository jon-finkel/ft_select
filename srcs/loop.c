/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:03:16 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/14 11:44:43 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int			remove_element(t_data *data, int *nb)
{
	char		buff[MAXPATHLEN + 1024];
	int			k;
	t_bool		space;

	*nb -= 1;
	data->select[data->pos] = FALSE;
	ft_strdel(&data->string);
	if (*nb > 0)
	{
		PROTECT(data->string = ft_strnew(0), -1);
		space = FALSE;
		k = -1;
		while (++k < data->argc)
			if (data->select[k] == TRUE)
			{
				ft_memset(buff, '\0', MAXPATHLEN + 1024);
				if (space == TRUE)
					ft_strcat(buff, " ");
				ft_strcat(buff, data->argv[k]);
				PROTECT(data->string = ft_strjoin(data->string, buff, E_FREE),\
					-1);
				space = TRUE;
			}
	}
	return (0);
}

static int			toggle_elem(t_data *data, int *nb)
{
	char		buff[MAXPATHLEN + 1024];

	ft_memset(buff, '\0', MAXPATHLEN + 1024);
	if (data->select[data->pos] == TRUE)
		NEG_PROTECT(remove_element(data, nb), -1);
	else
	{
		*nb += 1;
		if (*nb == 1)
			PROTECT(data->string = ft_strdup(data->argv[data->pos]), -1);
		else
		{
			ft_strcat(buff, " ");
			ft_strcat(buff, data->argv[data->pos]);
			PROTECT(data->string = ft_strjoin(data->string, buff, E_FREE), -1);
		}
		data->select[data->pos] = TRUE;
	}
	flag_underline(E_ENABLE, data->fd);
	NEG_PROTECT(color_output(data, data->pos, data->x, data->y), -1);
	flag_underline(E_DISABLE, data->fd);
	input_arrow(data, "\033[B");
	return (0);
}

static int			delete_element(t_data *data, int *nb)
{
	int		k;

	if (data->select[data->pos] == TRUE)
	{
		NEG_PROTECT(remove_element(data, nb), -1);
		if (!*nb)
			restore_config(data, E_EXIT_SUCCESS);
	}
	k = data->pos;
	while (data->argv[++k])
	{
		data->argv[k - 1] = data->argv[k];
		data->select[k - 1] = data->select[k];
	}
	data->argv[k] = NULL;
	--data->argc;
	if (data->pos)
		--data->pos;
	NEG_PROTECT(check_window_size(data), -1);
	return (0);
}

static int			full_toggle(t_data *data, int *nb, t_flag flag, int k)
{
	char		buff[1024];

	ft_strdel(&data->string);
	if (flag == E_DISABLE && !(data->pos = 0))
	{
		*nb = 0;
		while (++k < data->argc)
			data->select[k] = FALSE;
	}
	else
	{
		PROTECT(data->string = ft_strdup(data->argv[++k]), -1);
		while (++k < data->argc)
		{
			data->select[k] = TRUE;
			ft_memset(buff, '\0', 1024);
			ft_strcat(buff, " ");
			ft_strcat(buff, data->argv[k]);
			PROTECT(data->string = ft_strjoin(data->string, buff, E_FREE), -1);
		}
		data->select[0] = TRUE;
		*nb = k;
	}
	check_window_size(data);
	return (0);
}

int					loop(t_data *data)
{
	char			buff[5];
	static int		nb = 0;

	while (101010)
	{
		ft_memset(buff, '\0', 5);
		NEG_PROTECT(read(STDIN_FILENO, buff, 4), -1);
		if (*buff == 127 || ft_strnequ(buff, "\033[3~", 4))
			delete_element(data, &nb);
		else if ((*buff == 9 && toggle_help(data) == -1) || *buff == 10)
			break ;
		else if (ft_strequ(buff, "\033") || (ft_strnequ(buff, "\033", 1)
			&& input_arrow(data, buff) == -1))
			break ;
		else if ((*buff == 42 && full_toggle(data, &nb, E_ENABLE, -1) == -1)
			|| (*buff == 92 && full_toggle(data, &nb, E_DISABLE, -1) == -1))
			break ;
		else if (lettercheck(*buff) && dynamic_search(data, buff, 0) == -1)
			break ;
		else if ((*buff == 10 || *buff == 32) && toggle_elem(data, &nb) == -1)
			break ;
	}
	return (restore_config(data, (*buff == 10 ? E_OUTPUT : E_EXIT_SUCCESS)));
}
