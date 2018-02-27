/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 20:30:34 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/26 21:35:36 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void			output_file(t_data *data, struct stat *w_stat,
					const char *str, int k)
{
	if (w_stat && S_ISDIR(w_stat->st_mode))
		ft_dprintf(data->fd, "%s{1Gx}%s{eoc}", str, data->argv[k]);
	else if (w_stat && S_ISLNK(w_stat->st_mode))
		ft_dprintf(data->fd, "%s{fx}%s{eoc}", str, data->argv[k]);
	else if (w_stat && S_ISBLK(w_stat->st_mode))
		ft_dprintf(data->fd, "%s{eg}%s{eoc}", str, data->argv[k]);
	else if (w_stat && S_ISCHR(w_stat->st_mode))
		ft_dprintf(data->fd, "%s{ed}%s{eoc}", str, data->argv[k]);
	else if (w_stat && w_stat->st_mode & S_IXUSR)
		ft_dprintf(data->fd, "%s{Dx}%s{eoc}", str, data->argv[k]);
	else
		ft_dprintf(data->fd, "%s%s", str, data->argv[k]);
}

int					color_output(t_data *data, int k, int x, int y)
{
	char			file[MAXPATHLEN + 1048];
	char			*move;
	char			*str;
	struct stat		w_stat;

	ft_memset(file, '\0', MAXPATHLEN + 1048);
	if (data->select[k] == true)
		flag_reverse_video(E_ENABLE, data->fd);
	move = tgetstr("cm", NULL);
	str = tgoto(move, x, y);
	ft_sprintf(file, "%v/%s", "PWD", data->argv[k]);
	if (ft_strchr(data->argv[k], '/'))
		x = lstat(data->argv[k], &w_stat);
	else
		x = lstat(file, &w_stat);
	output_file(data, (x == -1 ? NULL : &w_stat), str, k);
	if (data->select[k] == true)
		flag_reverse_video(E_DISABLE, data->fd);
	KTHXBYE;
}
