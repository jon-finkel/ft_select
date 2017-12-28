/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 19:56:26 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/28 21:54:43 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int			search_letter(t_data *data, const char letter)
{
	static int		x = 0;

	if (!x && (letter == '\010' || letter == '\177'))
		return (0);
	return (0);
}

int					dynamic_search(t_data *data, char *buff)
{
	char		*move;
	char		*str;

	data->status = E_DYNAMIC;
	PROTECT(move = tgetstr("cm", NULL), -1);
	PROTECT(str = tgoto(move, 0, data->rows + (data->extra ? 4 : 3)), -1);
	ft_dprintf(data->fd, "%s{17H}  search file: {eoc}", str);
	while (101010)
	{
		ft_memset(buff, '\0', 4);
		NEG_PROTECT(read(STDIN_FILENO, buff, 3), -1);
		if (*buff > '\040' && *buff < '\177')
			search_letter(data, *buff);
		else if (ft_strequ(buff, "\033"))
			break ;
	}
	display_files(data);
	data->status = E_REGULAR;
	return (0);
}
