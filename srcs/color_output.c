/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 20:30:34 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/28 22:42:23 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void			output_file(t_data *data, struct stat w_stat,
					const char *str, const int fd)
{
	if (data->select[data->pos] == FALSE && S_ISDIR(w_stat.st_mode))
		ft_dprintf(fd, "%s{1Gx}%s{eoc}", str, data->argv[data->pos]);
	else if (data->select[data->pos] == FALSE && S_ISLNK(w_stat.st_mode))
		ft_dprintf(fd, "%s{fx}%s{eoc}", str, data->argv[data->pos]);
	else if (data->select[data->pos] == FALSE && S_ISBLK(w_stat.st_mode))
		ft_dprintf(fd, "%s{eg}%s{eoc}", str, data->argv[data->pos]);
	else if (data->select[data->pos] == FALSE && S_ISCHR(w_stat.st_mode))
		ft_dprintf(fd, "%s{ed}%s{eoc}", str, data->argv[data->pos]);
	else if (data->select[data->pos] == FALSE && w_stat.st_mode & S_IXUSR)
		ft_dprintf(fd, "%s{Dx}%s{eoc}", str, data->argv[data->pos]);
	else
		ft_dprintf(fd, "%s%s", str, data->argv[data->pos]);
}

int					color_output(t_data *data)
{
	char			*file;
	char			*move;
	char			*path;
	char			*str;
	struct stat		w_stat;

	PROTECT(move = tgetstr("cm", NULL), -1);
	PROTECT(str = tgoto(move, data->x, data->y), -1);
	PROTECT(path = getcwd(NULL, MAXPATHLEN), -1);
	NEG_PROTECT(ft_asprintf(&file, "%s/%s", path, data->argv[data->pos]), -1);
	if (ft_strchr(data->argv[data->pos], '/'))
		NEG_PROTECT(lstat(data->argv[data->pos], &w_stat), -1);
	else
		NEG_PROTECT(lstat(file, &w_stat), -1);
	ft_cleanup(4, E_PTR, file, E_PTR, path);
	if (data->select[data->pos] == TRUE)
		flag_reverse_video(E_ENABLE, data->fd);
	output_file(data, w_stat, str, data->fd);
	if (data->select[data->pos] == TRUE)
		flag_reverse_video(E_DISABLE, data->fd);
	return (0);
}
