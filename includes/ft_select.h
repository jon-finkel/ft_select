/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:44:05 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/31 09:27:21 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <dirent.h>
# include <locale.h>
# include <signal.h>
# include <sys/fcntl.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <termcap.h>
# include <termios.h>
# include "../libft/includes/libft.h"

typedef enum		s_flag
{
	E_REGULAR,
	E_HELP,
	E_ENABLE,
	E_DISABLE,
	E_EXIT_SUCCESS,
	E_EXIT_FAILURE,
	E_OUTPUT,
	E_SUSPEND
}					t_flag;

typedef struct		s_data
{
	char			*string;
	char			**argv;
	t_bool			*select;
	int				fd;
	int				argc;
	int				pos;
	int				padding;
	int				x;
	int				y;
	int				curr_column;
	int				columns;
	int				rows;
	int				extra;
	size_t			width;
	struct termios	*oldcc;
	t_flag			status;
}					t_data;

int					check_window_size(t_data *data);
int					color_output(t_data *data, int k, int x, int y);
int					display_files(t_data *data, unsigned short ws_col);
int					display_help(t_data *data, unsigned short ws_col);
int					dynamic_search(t_data *data, char *buff, int x);
int					flag_reverse_video(t_flag flag, const int fd);
int					flag_underline(t_flag flag, const int fd);
void				get_coordinates(t_data *data);
int					initialize_termios(t_data *data);
int					input_arrow(t_data *data, const char *const buff);
int					loop(t_data *data);
int					restore_configuration(t_data *data, t_flag flag);
void				signal_handler(int signo);
int					toggle_help(t_data *data);

#endif
