/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 20:30:34 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/28 21:50:34 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			color_output(t_data *data)
{
	char			*file;
	char			*move;
	char			*path;
	char			*str;
	struct stat		w_stat;

	PROTECT(move = tgetstr("cm", NULL), -1);
	PROTECT(str = tgoto(move, data->x, data->y), -1);
	PROTECT(path = ft_strnew(MAXPATHLEN), -1);
	PROTECT(path = getcwd(path, MAXPATHLEN), -1);
	NEG_PROTECT(ft_asprintf(&file, "%s/%s", path, data->argv[data->pos]), -1);
	NEG_PROTECT(stat(file, &w_stat), -1);
	ft_cleanup(4, E_PTR, file, E_PTR, path);
	if (data->select[data->pos] == TRUE)
		flag_reverse_video(E_ENABLE, data->fd);
	if (S_ISDIR(w_stat.st_mode))
		ft_dprintf(data->fd, "%s{1Gx}%s{eoc}", str, data->argv[data->pos]);
	else if (w_stat.st_mode & S_IXUSR)
		ft_dprintf(data->fd, "%s{Dx}%s{eoc}", str, data->argv[data->pos]);
	else
		ft_dprintf(data->fd, "%s%s", str, data->argv[data->pos]);
	if (data->select[data->pos] == TRUE)
		flag_reverse_video(E_DISABLE, data->fd);
	return (0);
}
