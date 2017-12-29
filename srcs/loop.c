/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:03:16 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/29 16:48:14 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int			toggle_element(t_data *data, int *nb)
{
	if (data->select[data->pos] == TRUE)
	{
		*nb -= 1;
		data->select[data->pos] = FALSE;
	}
	else
	{
		*nb += 1;
		data->select[data->pos] = TRUE;
	}
	input_arrow(data, "\033[B");
	flag_underline(E_ENABLE, data->fd);
	NEG_PROTECT(color_output(data), -1);
	flag_underline(E_DISABLE, data->fd);
	return (0);
}

static int			delete_element(t_data *data, int *nb)
{
	if (*nb < 1)
		restore_configuration(data, E_EXIT_SUCCESS);
	if (data->select[data->pos] == TRUE)
		toggle_element(data, nb);
	return (0);
}

static int			toggle_help(t_data *data)
{
	char		buff[4];

	data->status = E_HELP;
	NEG_PROTECT(display_help(data), -1);
	while (101010)
	{
		ft_memset(buff, '\0', 4);
		NEG_PROTECT(read(STDIN_FILENO, &buff, 3), -1);
		if (ft_strequ(buff, "\033"))
			return (-1);
		else if (ft_strequ(buff, "\011"))
			break ;
	}
	data->status = E_REGULAR;
	display_files(data);
	return (0);
}

int					loop(t_data *data)
{
	char			buff[4];
	static int		nb = 0;

	ft_interceptor(&signal_handler, 2, SIGINT, SIGWINCH);
	NEG_PROTECT(display_files(data), -1);
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
		else if (ft_strequ(buff, "\033") || input_arrow(data, buff) == -1)
			break ;
		else if ((*buff > '\040' && *buff < '\177')
			&& dynamic_search(data, buff, 0) == -1)
			break ;
		else if ((ft_strequ(buff, "\040") || ft_strequ(buff, "\012"))
			&& toggle_element(data, &nb) == -1)
			break ;
	}
	return (restore_configuration(data, E_DISABLE));
}
