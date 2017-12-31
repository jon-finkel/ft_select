/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:03:16 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/31 09:32:40 by nfinkel          ###   ########.fr       */
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

static int			toggle_element(t_data *data, int *nb)
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
	if (!*nb)
		restore_configuration(data, E_EXIT_SUCCESS);
	if (data->select[data->pos] == TRUE)
		NEG_PROTECT(toggle_element(data, nb), -1);
	return (0);
}

int					loop(t_data *data)
{
	char			buff[4];
	static int		nb = 0;

	while (101010)
	{
		ft_memset(buff, '\0', 4);
		NEG_PROTECT(read(STDIN_FILENO, &buff, 3), -1);
		if (ft_strequ(buff, "\010") || ft_strequ(buff, "\177"))
			delete_element(data, &nb);
		else if (ft_strequ(buff, "\011") && toggle_help(data) == -1)
			break ;
		else if (ft_strequ(buff, "\012"))
			return (restore_configuration(data, E_OUTPUT));
		else if (ft_strequ(buff, "\033") || (ft_strnequ(buff, "\033", 1)
			&& input_arrow(data, buff) == -1))
			break ;
		else if ((*buff > '\040' && *buff < '\177')
			&& dynamic_search(data, buff, 0) == -1)
			break ;
		else if ((ft_strequ(buff, "\040") || ft_strequ(buff, "\012"))
			&& toggle_element(data, &nb) == -1)
			break ;
	}
	return (restore_configuration(data, E_EXIT_SUCCESS));
}
